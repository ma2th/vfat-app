// Copyright 2019 Matthias Ring
// Machine Learning and Data Analytics Lab
// Friedrich-Alexander-University Erlangen-Nuremberg
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ProgramTester.h"

#include "Engine/World.h"

#include "Models/VisualField.h"
#include "Models/OctopusG1Field.h"
#include "Models/EquidistantField.h"
#include "Models/TrainingField.h"
#include "Utilities/Constants.h"
#include "Utilities/MathUtilities.h"
#include "Utilities/WorldUtilities.h"


void UProgramTester::Init(USingleEyeComponent* MovingComponent, UWorld* World)
{
    HasTestStarted = false;
    ResponseValid = false;
    BlindSpotTesting = false;
    FalsePositives = 0;
    BlindSpotFalsePositives = 0;
    RemainingBlindSpotTests = -1;
    
    this->World = World;
    this->MovingComponent = MovingComponent;
    
    ReactionTimer = NewObject<UReactionTimer>(this);
}

void UProgramTester::SetProgram(FEquidistantProgram Program)
{
    UEquidistantField* Field = NewObject<UEquidistantField>(this);
    Field->Init(Program);
    
    this->Program = Program;
    this->VisualField = Field;
    this->NumBlindSpotTests = Program.Blind_Spot_Tests;
    this->RemainingBlindSpotTests = Program.Blind_Spot_Tests;
}

void UProgramTester::SetProgram(FOctopusG1Program Program)
{
    UOctopusG1Field* Field = NewObject<UOctopusG1Field>(this);
    Field->Init(Program);
    
    this->Program = Program;
    this->VisualField = Field;
    this->NumBlindSpotTests = Program.Blind_Spot_Tests;
    this->RemainingBlindSpotTests = Program.Blind_Spot_Tests;
}

void UProgramTester::SetProgram(FTrainingProgram Program)
{
    UTrainingField* Field = NewObject<UTrainingField>(this);
    Field->Init(Program);
    
    this->Program = Program;
    this->VisualField = Field;
    this->NumBlindSpotTests = 0;
    this->RemainingBlindSpotTests = 0;
}

void UProgramTester::ButtonPressed()
{
    if (HasTestStarted)
    {
        ProcessAnswer();
    }
    else
    {
        HasTestStarted = true;
        TestStartTime = FDateTime::Now();
        MovingComponent->MoveToCenter();
        MovingComponent->SetVisibility(true);
    
        World->GetTimerManager().ClearTimer(TestTimer);
        World->GetTimerManager().SetTimer(TestTimer, this, &UProgramTester::ShowNextTest, 5.0f, false);
    }
}

void UProgramTester::ProcessAnswer()
{
    Mutex.Lock();
    if (ResponseValid)
    {
        float Time = ReactionTimer->StopTiming();
        if (Time >= Program.Min_Response_Time)
        {
            if (BlindSpotTesting)
            {
                BlindSpotFalsePositives++;
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Position detected"));
                VisualField->LastPositionWasDetected();
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Response too fast: %f < %f"), Time, Program.Min_Response_Time);
            UE_LOG(LogTemp, Log, TEXT("False positive #%d"), FalsePositives + 1);
            FalsePositives++;
        }
        ResponseValid = false;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("False positive #%d"), FalsePositives + 1);
        FalsePositives++;
    }
    Mutex.Lock();
}

void UProgramTester::ShowNextTest()
{
    ResponseValid = false;
    BlindSpotTesting = false;

    World->GetTimerManager().ClearTimer(TestTimer);
    
    if (VisualField->HasMoreUntestedPositions() || RemainingBlindSpotTests > 0)
    {
        float TestTime = FMath::FRand() * (Program.Max_Waiting_Time / 1000.0f - Program.Min_Waiting_Time / 1000.0f) + Program.Min_Waiting_Time / 1000.0f;
        
        if (RemainingBlindSpotTests > 0)
        {
            float BlindSpotRandom = FMath::FRand() * (NumBlindSpotTests + VisualField->NumTestPositions());
            
            if (BlindSpotRandom <= NumBlindSpotTests || !VisualField->HasMoreUntestedPositions())
            {
                BlindSpotTesting = true;
                RemainingBlindSpotTests--;
            }
        }
        
        if (BlindSpotTesting)
        {
            MovingComponent->MoveToBlindSpot();
        }
        else
        {
            UpdatePositionAndThreshold();
        }
        MovingComponent->SetVisibility(true);
        
        Mutex.Lock();
        ResponseValid = true;
        ReactionTimer->StartTiming();
        Mutex.Unlock();
        
        World->GetTimerManager().SetTimer(DisplayTimer, this, &UProgramTester::OnDisplayTimer, Program.Display_Time / 1000.0f, false);
        World->GetTimerManager().SetTimer(ResponseTimer, this, &UProgramTester::OnResponseTimer, Program.Max_Response_Time / 1000.0f, false);
        World->GetTimerManager().SetTimer(TestTimer, this, &UProgramTester::ShowNextTest, TestTime, false);
    }
    else
    {
        MovingComponent->SetVisibility(false);
        TestEndTime = FDateTime::Now();
        ProgramDoneCallback.ExecuteIfBound();
    }
}

void UProgramTester::UpdatePositionAndThreshold()
{
    float OutLongitude;
    float OutLatitude;
    int32 OutThresholdIndex;
    int32 OutEye;
    
    VisualField->NextUntestedPosition(OutLongitude, OutLatitude, OutThresholdIndex, OutEye);
    WorldUtilities::MoveComponent(MovingComponent, OutLongitude, OutLatitude, Constants::MESH_RADIUS);
    MovingComponent->SetThresholdAndEye(OutThresholdIndex, OutEye);
}

void UProgramTester::OnDisplayTimer()
{
    MovingComponent->SetVisibility(false);
    World->GetTimerManager().ClearTimer(DisplayTimer);
}

void UProgramTester::OnResponseTimer()
{
    Mutex.Lock();
    ResponseValid = false;
    if (!BlindSpotTesting)
    {
        VisualField->LastPositionWasNotDetected();
    }
    Mutex.Unlock();
    World->GetTimerManager().ClearTimer(ResponseTimer);
}

FDateTime UProgramTester::GetTestStartTime()
{
    return TestStartTime;
}

FDateTime UProgramTester::GetTestEndTime()
{
    return TestEndTime;
}

int32 UProgramTester::GetFalsePositives()
{
    return FalsePositives;
}

int32 UProgramTester::GetBlindSpotFalsePositives()
{
    return BlindSpotFalsePositives;
}

UVisualField* UProgramTester::GetVisualField()
{
    return VisualField;
}

FAbstractProgram UProgramTester::GetProgram()
{
    return Program;
}

FString UProgramTester::ResultAsCSVString()
{
    return VisualField->ResultAsCSVString();
}




