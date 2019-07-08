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

#include "CalibrationMenu.h"

#include "Utilities/Constants.h"

void UCalibrationMenu::Init(FAbstractProgram Program)
{
    AVFATPawn* Pawn = Cast<AVFATPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    FixationComponent = Pawn->GetFixationComponent1();
    FixationComponent->ActivateCalibrationMode(Program, true);
    
    MovingComponent = Pawn->GetMovingComponent();
    MovingComponent->ActivateCalibrationMode(Program, false);
    
    this->Program = Program;
    this->ThresholdIndex = Program.ThresholdsAsArray.Num();
    
    NextThresholdClicked();
}

void UCalibrationMenu::NextThresholdClicked()
{
    if (--ThresholdIndex < 0)
    {
        ThresholdIndex = Program.ThresholdsAsArray.Num();
        
        FixationComponent->SetVisibility(true);
        MovingComponent->SetVisibility(false);
        
        ReceiveThreshold(TEXT("Fixation color"));
    }
    else
    {
        MovingComponent->SetThresholdAndEye(ThresholdIndex, Constants::BOTH_EYES);
        
        MovingComponent->SetVisibility(true);
        FixationComponent->SetVisibility(false);
        
        ReceiveThreshold(FString::Printf(TEXT("Assessment color at %.1f dB"), Program.ThresholdsAsArray[ThresholdIndex]));
    }
}

void UCalibrationMenu::DoneClicked()
{
    RemoveFromViewport();
    CalibrationDoneCallback.ExecuteIfBound();
}
