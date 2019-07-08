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
#include "TimerManager.h"
#include "UObject/NoExportTypes.h"
#include "HAL/ThreadSafeBool.h"

#include "Models/VisualField.h"
#include "Models/ProgramManagement.h"
#include "Components/SingleEyeComponent.h"
#include "Controller/ReactionTimer.h"

#include "ProgramTester.generated.h"


UCLASS()
class UProgramTester : public UObject
{
    GENERATED_BODY()
    
    DECLARE_DELEGATE(ProgramDoneDelegate)
    
public:
    void Init(USingleEyeComponent* MovingComponent, UWorld* World);

    void SetProgram(FEquidistantProgram Program);
    
    void SetProgram(FOctopusG1Program Program);
    
    void SetProgram(FTrainingProgram Program);
    
    void ButtonPressed();
    
    FDateTime GetTestStartTime();
    
    FDateTime GetTestEndTime();
    
    int32 GetFalsePositives();
    
    int32 GetBlindSpotFalsePositives();
    
    FAbstractProgram GetProgram();
    
    FString ResultAsCSVString();
    
    UVisualField* GetVisualField();
    
    ProgramDoneDelegate ProgramDoneCallback;
   
private:
    void ProcessAnswer();
    
    void ShowNextTest();
   
    void UpdatePositionAndThreshold();
    
    void BlindSpotPositionAndThreshold();
    
    void MoveComponent(float Longitude, float Latitude);
    
    void OnResponseTimer();
    
    void OnDisplayTimer();
    
    UPROPERTY()
    USingleEyeComponent* MovingComponent;
    
    UPROPERTY()
    UWorld* World;
    
    UPROPERTY()
    UReactionTimer* ReactionTimer;
    
    UPROPERTY()
    UVisualField* VisualField;
    
    FAbstractProgram Program;
    
    FDateTime TestStartTime;
    
    FDateTime TestEndTime;
    
    bool HasTestStarted;
    
    int32 FalsePositives;
    
    int32 BlindSpotFalsePositives;
    
    int32 RemainingBlindSpotTests;
    
    int32 NumBlindSpotTests;
    
    FTimerHandle TestTimer;
    
    FTimerHandle ResponseTimer;
    
    FTimerHandle DisplayTimer;
    
    FThreadSafeBool ResponseValid;
    
    FThreadSafeBool BlindSpotTesting;
    
    FCriticalSection Mutex;
};
