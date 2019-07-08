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
#include "Runtime/Online/HTTP/Public/Http.h"

#include "Models/ProgramManagement.h"
#include "Utilities/PersistencyUtilities.h"

#include "ProgramMenu.generated.h"


UCLASS()
class UProgramMenu : public UUserWidget
{
    GENERATED_BODY()
    
    DECLARE_DELEGATE(LoggedOutDelegate)
    DECLARE_DELEGATE_OneParam(CalibrateDelegate, FAbstractProgram)
    DECLARE_DELEGATE_OneParam(EquidistantSelectedDelegate, FEquidistantProgram)
    DECLARE_DELEGATE_OneParam(OctopusG1SelectedDelegate, FOctopusG1Program)
    DECLARE_DELEGATE_OneParam(TrainingSelectedDelegate, FTrainingProgram)
    
public:
    void Init(UPersistentSettings* Settings);
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void StartClicked(const FString SelectedProgramName);
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void CalibrateClicked(const FString SelectedProgramName);
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void LogoutClicked();
    
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void ReceivePrograms(const TArray<FString>& Programs);
    
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void ReceiveMessage(const FString& Message);
    
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void ReceiveButtonState(const bool Enable);
    
    void OnEquidistantListResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    void OnOctopusG1ListResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    void OnTrainingListResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    void OnEquidistantDetailResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    void OnOctopusG1DetailResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    void OnTrainingDetailResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    LoggedOutDelegate LoggedOutCallback;
    
    CalibrateDelegate CalibrateCallback;
    
    EquidistantSelectedDelegate EquidistantSelectedCallback;
    
    OctopusG1SelectedDelegate OctopusG1SelectedCallback;
    
    TrainingSelectedDelegate TrainingSelectedCallback;
    
private:
    void GetProgramDetails(const FString SelectedProgramName);
    
    void FillComboBox(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, TArray<FProgramShortInfo>* CurrentList);
    
    UPROPERTY()
    UPersistentSettings* Settings;
    
    TArray<FProgramShortInfo> EquidistantList;
    
    TArray<FProgramShortInfo> OctopusG1List;
    
    TArray<FProgramShortInfo> TrainingList;
    
    bool EquidistantListLoaded;
    
    bool OctopusG1ListLoaded;
    
    bool TrainingListLoaded;
    
    bool StartWasClicked;
    
    bool CalibrateWasClicked;
    
    FCriticalSection Mutex;
};
