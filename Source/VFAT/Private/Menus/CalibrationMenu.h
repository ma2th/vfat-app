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

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "VFATPawn.h"
#include "Models/ProgramManagement.h"
#include "Utilities/Constants.h"

#include "CalibrationMenu.generated.h"


UCLASS()
class UCalibrationMenu : public UUserWidget
{
	GENERATED_BODY()

    DECLARE_DELEGATE(CalibrationDoneDelegate)
    
public:
    void Init(FAbstractProgram Program);
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void NextThresholdClicked();
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void DoneClicked();
    
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void ReceiveThreshold(const FString& Threshold);
    
    CalibrationDoneDelegate CalibrationDoneCallback;
    
private:
    UPROPERTY()
    USingleEyeComponent* FixationComponent;
    
    UPROPERTY()
    USingleEyeComponent* MovingComponent;
    
    FAbstractProgram Program;
    
    int32 ThresholdIndex;
 };
