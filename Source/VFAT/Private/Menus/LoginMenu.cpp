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


#include "LoginMenu.h"

#include "Json.h"
#include "JsonUtilities.h"

#include "Utilities/Constants.h"
#include "Utilities/HttpUtilities.h"
#include "Utilities/PersistencyUtilities.h"


void ULoginMenu::Init(UPersistentSettings* Settings)
{
    this->Settings = Settings;
}

void ULoginMenu::LoginClicked(FString Email, FString Password)
{
    ReceiveButtonState(false);
    
    TMap<FString, FString> FormFields;
    
    FormFields.Add(TEXT("username"), *Email);
    FormFields.Add(TEXT("password"), *Password);
    
    HttpUtilities::SendPostRequest(Constants::API_TOKEN, this, &ULoginMenu::OnLoginResponse, nullptr, &FormFields);
    
    ReceiveMessage(*Constants::MESSAGE_CONNECTING);
}

void ULoginMenu::RegisterClicked()
{
    FGenericPlatformProcess::LaunchURL(*Constants::SERVER_URL, nullptr, nullptr);
}

void ULoginMenu::OnLoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    if (Successful) {
        FString UserToken = TEXT("");
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
        
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject->HasField(Constants::API_TOKEN_RESPONSE_FIELD))
        {
            UserToken = JsonObject->GetStringField(Constants::API_TOKEN_RESPONSE_FIELD);
        }
        
        if (!UserToken.Equals(TEXT("")))
        {
            Settings->Token = UserToken;
            PersistencyUtilities::SaveSettings(Settings);
            
            RemoveFromViewport();
            LoggedInCallback.ExecuteIfBound();
        }
        else
        {
            ReceiveMessage(*Constants::MESSAGE_INVALID_CREDENTIALS);
        }
    }
    else
    {
        ReceiveMessage(*Constants::MESSAGE_CONNECTION_ERROR);
    }
    ReceiveButtonState(true);
}


