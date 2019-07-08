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
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Models/ProgramManagement.h"

#include "SingleEyeComponent.generated.h"


UCLASS()
class USingleEyeComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
		
public:
    void SetupMaterial(UMaterialInterface* Material);
    
    void ActivateProgramMode(FAbstractProgram Program, bool IsFixationComponent, bool RandomColor);
    
    void ActivateCalibrationMode(FAbstractProgram Program, bool IsFixationComponent);
 
    void SetThresholdAndEye(int32 ThresholdIndex, int32 Eye);
    
    void MoveToBlindSpot();
    
    void MoveToCenter();
    
private:
    void SetEye(int32 Eye);
    
    void SetColor(FLinearColor Color);
    
    void SetThreshold(int32 ThresholdIndex);
    
    UPROPERTY()
    UMaterialInstanceDynamic* MaterialInstance;

    FLinearColor BaseColor;
    
    FAbstractProgram Program;
    
    bool RandomColor;
};
