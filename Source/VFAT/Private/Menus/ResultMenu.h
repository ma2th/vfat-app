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

#include "Controller/ProgramTester.h"
#include "Utilities/PersistencyUtilities.h"

#include "ResultMenu.generated.h"


UCLASS()
class UResultMenu : public UUserWidget
{
	GENERATED_BODY()
	
    DECLARE_DELEGATE(RestartRequestDelegate)
    
public:
    void Init(UPersistentSettings* Settings, UProgramTester* Tester);
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void RestartClicked();
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void LogoutClicked();
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void RetryUploadClicked();
	
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void ReceiveMessage(const FString& Message);
    
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void RetryButtonVisibility(const bool Visible);
    
    void OnUploadResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    RestartRequestDelegate RestartRequestCallback;
    
private:
    void UploadResult();
    
    void UploadResultHelper(FString ApiEndpoint);
    
    UPROPERTY()
    UPersistentSettings* Settings;
    
    UPROPERTY()
    UProgramTester* Tester;
};
