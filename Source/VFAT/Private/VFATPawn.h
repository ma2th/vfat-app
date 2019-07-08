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
#include "HAL/ThreadSafeBool.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

#include "Models/ProgramManagement.h"
#include "Controller/ProgramTester.h"
#include "Components/SingleEyeComponent.h"

#include "VFATPawn.generated.h"


UCLASS()
class AVFATPawn : public APawn
{
	GENERATED_BODY()

public:
	AVFATPawn();
    
    virtual void Tick(float DeltaTime) override;
    
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    
    void StartProgram(FEquidistantProgram Program);
    
    void StartProgram(FOctopusG1Program Program);
    
    void StartProgram(FTrainingProgram Program);

    void ButtonPressed();
    
    void ProgramDone();
    
    USingleEyeComponent* GetFixationComponent1();
    
    USingleEyeComponent* GetMovingComponent();
    
protected:
	virtual void BeginPlay() override;
    
private:
    void ConstructionTimeSetup();
    
    void RuntimeSetup();
    
    USingleEyeComponent* CreateInteractionComponent(UStaticMesh* Mesh, UMaterialInterface* Material);
    
    void UploadResult();
    
    void OnUploadResponse();
    
    void PrepareProgramStart(FAbstractProgram Program, bool RandomColor);

    UPROPERTY()
    UCameraComponent* VRCamera;
    
    UPROPERTY()
    USceneComponent* VRCameraScene;
    
    UPROPERTY()
    USingleEyeComponent* FixationComponent1;
    
    UPROPERTY()
    USingleEyeComponent* FixationComponent2;
    
    UPROPERTY()
    USingleEyeComponent* FixationComponent3;
    
    UPROPERTY()
    USingleEyeComponent* FixationComponent4;
    
    UPROPERTY()
    USingleEyeComponent* MovingComponent;
    
    UPROPERTY()
    UProgramTester* Tester;
    
    FThreadSafeBool ProgramRunning;
};
