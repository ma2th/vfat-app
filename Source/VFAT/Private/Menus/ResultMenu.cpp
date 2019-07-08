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

#include "ResultMenu.h"

#include "Models/VisualField.h"
#include "Models/EquidistantField.h"
#include "Models/OctopusG1Field.h"
#include "Models/TrainingField.h"
#include "Utilities/TextUtilities.h"
#include "Utilities/HttpUtilities.h"


void UResultMenu::Init(UPersistentSettings* Settings, UProgramTester* Tester)
{
    this->Settings = Settings;
    this->Tester = Tester;
    
    UploadResult();
}

void UResultMenu::UploadResult()
{
    UVisualField* Field = Tester->GetVisualField();
    if (Cast<UEquidistantField>(Field))
    {
        UploadResultHelper(Constants::API_UPLOAD_EQUIDISTANT);
    }
    else if (Cast<UOctopusG1Field>(Field))
    {
        UploadResultHelper(Constants::API_UPLOAD_OCTOPUSG1);
    } else if (Cast<UTrainingField>(Field)) {
        RetryButtonVisibility(false);
    }
}

void UResultMenu::UploadResultHelper(FString ApiEndpoint)
{
    TMap<FString, FString> FormFields;
    TMap<FString, FString> TextFiles;
    
    RetryButtonVisibility(false);
    ReceiveMessage(*Constants::MESSAGE_UPLOADING);
    
    FDateTime Start = Tester->GetTestStartTime();
    FDateTime End = Tester->GetTestEndTime();
    FTimespan Duration = End - Start;
    
    FString FileAsString = Tester->ResultAsCSVString();
    TextFiles.Add(Constants::HTTP_REQUEST_FILE_FIELD_LABEL, FileAsString);
    
    FormFields.Add(Constants::HTTP_REQUEST_DURATION_FIELD_LABEL, FString::Printf(TEXT("%s:%s:%s"), *TextUtilities::PrefixPadding(FString::FromInt(Duration.GetHours()), TEXT("0"), 2), *TextUtilities::PrefixPadding(FString::FromInt(Duration.GetMinutes()), TEXT("0"), 2), *TextUtilities::PrefixPadding(FString::FromInt(Duration.GetSeconds()), TEXT("0"), 2)));
    FormFields.Add(Constants::HTTP_REQUEST_FALSE_POSITIVES_FIELD_LABEL, FString::FromInt(Tester->GetFalsePositives()));
    FormFields.Add(Constants::HTTP_REQUEST_EYE_FIELD_LABEL, FString::FromInt(Tester->GetProgram().Eye));
    FormFields.Add(Constants::HTTP_REQUEST_CONFIGURATION_FIELD_LABEL, FString::FromInt(Tester->GetProgram().Id));
    FormFields.Add(Constants::HTTP_REQUEST_BLIND_SPOT_FALSE_POSITIVES_FIELD_LABEL, FString::FromInt(Tester->GetBlindSpotFalsePositives()));
    
    TMap<FString, FString> Header = HttpUtilities::CreateAuthorizationHeader(Settings->Token);
    HttpUtilities::SendPostRequest(ApiEndpoint, this, &UResultMenu::OnUploadResponse, &Header, &FormFields, &TextFiles);
}

void UResultMenu::OnUploadResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    if (Successful) {
        ReceiveMessage(TEXT("Result successfully uploaded"));
    }
    else
    {
        ReceiveMessage(*Constants::MESSAGE_CONNECTION_ERROR);
        RetryButtonVisibility(true);
    }
}

void UResultMenu::RetryUploadClicked()
{
    UploadResult();
}

void UResultMenu::RestartClicked()
{
    RemoveFromViewport();
    RestartRequestCallback.ExecuteIfBound();
}

void UResultMenu::LogoutClicked()
{
    Settings->Token = TEXT("");
    PersistencyUtilities::SaveSettings(Settings);
    
    RestartClicked();
}
