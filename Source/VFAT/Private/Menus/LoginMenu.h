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

#include "Models/PersistentSettings.h"

#include "LoginMenu.generated.h"


UCLASS()
class ULoginMenu : public UUserWidget
{
    GENERATED_BODY()
    
    DECLARE_DELEGATE(LoggedInDelegate)
    
public:
    void Init(UPersistentSettings* Settings);
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void LoginClicked(FString Email, FString Password);
    
    UFUNCTION(BlueprintCallable, Category="VFAT")
    void RegisterClicked();
    
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void ReceiveMessage(const FString& Result);
    
    UFUNCTION(BlueprintImplementableEvent, Category="VFAT")
    void ReceiveButtonState(const bool Enable);
    
    void OnLoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
    
    LoggedInDelegate LoggedInCallback;
    
private:
    UPROPERTY()
    UPersistentSettings* Settings;
};
