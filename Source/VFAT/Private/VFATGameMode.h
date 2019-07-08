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
#include "GameFramework/GameModeBase.h"

#include "Menus/LoginMenu.h"
#include "Menus/ProgramMenu.h"
#include "Menus/ResultMenu.h"
#include "Menus/CalibrationMenu.h"
#include "Models/ProgramManagement.h"
#include "Controller/ProgramTester.h"

#include "VFATGameMode.generated.h"


UCLASS()
class AVFATGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    void ShowLoginMenu();
    
    void LoggedIn();
    
    void RestartGame();
    
    void StartEquidistantProgram(FEquidistantProgram Program);
    
    void StartCalibration(FAbstractProgram Program);
    
    void StartOctopusG1Program(FOctopusG1Program Program);
    
    void StartTrainingProgram(FTrainingProgram Program);
    
    void TestResult(UProgramTester* Tester);
    
    void OnUploadResponse();
    
    UPROPERTY(EditAnywhere, Category="VFAT")
    UMaterialInterface* SingleEyeMaterial;
	
	UPROPERTY(EditAnywhere, Category="VFAT")
    UStaticMesh* FixationMesh;
    
    UPROPERTY(EditAnywhere, Category="VFAT")
    UStaticMesh* MovingMesh;
    
    UPROPERTY(EditAnywhere, Category = "VFAT")
    TSubclassOf<ULoginMenu> LoginMenuClass;
    
    UPROPERTY(EditAnywhere, Category = "VFAT")
    TSubclassOf<UProgramMenu> ProgramMenuClass;
    
    UPROPERTY(EditAnywhere, Category = "VFAT")
    TSubclassOf<UCalibrationMenu> CalibrationMenuClass;
    
    UPROPERTY(EditAnywhere, Category = "VFAT")
    TSubclassOf<UResultMenu> ResultMenuClass;
    
protected:
    virtual void BeginPlay() override;
    
private:
    void InitiateLoginProcedure();
    
    UPROPERTY()
    UPersistentSettings* Settings;
    
    UPROPERTY()
    ULoginMenu* LoginMenu;
    
    UPROPERTY()
    UProgramMenu* ProgramMenu;
    
    UPROPERTY()
    UCalibrationMenu* CalibrationMenu;
    
    UPROPERTY()
    UResultMenu* ResultMenu;
};
