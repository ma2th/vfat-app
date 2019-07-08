// Copyright 2019ß Matthias Ring
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

#include "VFATGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "VFATPawn.h"
#include "Utilities/WorldUtilities.h"
#include "Utilities/PersistencyUtilities.h"


void AVFATGameMode::BeginPlay()
{
    InitiateLoginProcedure();
}

void AVFATGameMode::InitiateLoginProcedure()
{
    Settings = PersistencyUtilities::LoadSettings();
    if (Settings && !Settings->Token.Equals(TEXT("")))
    {
        LoggedIn();
    }
    else
    {
        Settings = PersistencyUtilities::CreateSettingsObject();
        ShowLoginMenu();
    }
}

void AVFATGameMode::ShowLoginMenu()
{
    LoginMenu = WorldUtilities::CreateMenu<ULoginMenu>(GetWorld(), LoginMenuClass.Get());
    if (LoginMenu)
    {
        LoginMenu->Init(Settings);
        LoginMenu->LoggedInCallback.BindUObject(this, &AVFATGameMode::LoggedIn);
        LoginMenu->AddToViewport();
    }
    else
    {
        WorldUtilities::ShowErrorAndQuit(TEXT("Main menu cannot be created"), GetWorld());
    }
}

void AVFATGameMode::LoggedIn()
{
    ProgramMenu = WorldUtilities::CreateMenu<UProgramMenu>(GetWorld(), ProgramMenuClass.Get());
    if (ProgramMenu)
    {
        ProgramMenu->Init(Settings);
        ProgramMenu->LoggedOutCallback.BindUObject(this, &AVFATGameMode::RestartGame);
        ProgramMenu->CalibrateCallback.BindUObject(this, &AVFATGameMode::StartCalibration);
        ProgramMenu->EquidistantSelectedCallback.BindUObject(this, &AVFATGameMode::StartEquidistantProgram);
        ProgramMenu->OctopusG1SelectedCallback.BindUObject(this, &AVFATGameMode::StartOctopusG1Program);
        ProgramMenu->TrainingSelectedCallback.BindUObject(this, &AVFATGameMode::StartTrainingProgram);
        ProgramMenu->AddToViewport();
    }
    else
    {
        WorldUtilities::ShowErrorAndQuit(TEXT("Program menu cannot be created"), GetWorld());
    }
}

void AVFATGameMode::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetMapName()), true);
}

void AVFATGameMode::StartEquidistantProgram(FEquidistantProgram Program)
{
    AVFATPawn* Pawn = Cast<AVFATPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    Pawn->StartProgram(Program);
}

void AVFATGameMode::StartOctopusG1Program(FOctopusG1Program Program)
{
    AVFATPawn* Pawn = Cast<AVFATPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    Pawn->StartProgram(Program);
}

void AVFATGameMode::StartTrainingProgram(FTrainingProgram Program)
{
    AVFATPawn* Pawn = Cast<AVFATPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    Pawn->StartProgram(Program);
}

void AVFATGameMode::StartCalibration(FAbstractProgram Program)
{
    CalibrationMenu = WorldUtilities::CreateMenu<UCalibrationMenu>(GetWorld(), CalibrationMenuClass.Get());
    if (CalibrationMenu)
    {
        CalibrationMenu->CalibrationDoneCallback.BindUObject(this, &AVFATGameMode::LoggedIn);
        CalibrationMenu->Init(Program);
        CalibrationMenu->AddToViewport();
    }
    else
    {
        WorldUtilities::ShowErrorAndQuit(TEXT("Calibration menu cannot be created"), GetWorld());
    }
}

void AVFATGameMode::TestResult(UProgramTester* Tester)
{
    ResultMenu = WorldUtilities::CreateMenu<UResultMenu>(GetWorld(), ResultMenuClass.Get());
    if (ResultMenu)
    {
        ResultMenu->Init(Settings, Tester);
        ResultMenu->RestartRequestCallback.BindUObject(this, &AVFATGameMode::RestartGame);
        ResultMenu->AddToViewport();
    }
    else
    {
        WorldUtilities::ShowErrorAndQuit(TEXT("Result menu cannot be created"), GetWorld());
    }
}
