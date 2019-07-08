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

#include "ProgramMenu.h"

#include "Json.h"
#include "JsonUtilities.h"

#include "Utilities/Constants.h"
#include "Utilities/ArrayUtilities.h"
#include "Utilities/HttpUtilities.h"


void UProgramMenu::Init(UPersistentSettings* Settings)
{
    StartWasClicked = false;
    CalibrateWasClicked = false;
    
    EquidistantListLoaded = false;
    OctopusG1ListLoaded = false;
    TrainingListLoaded = false;
    
    EquidistantList.Empty();
    OctopusG1List.Empty();
    
    TMap<FString, FString> Header = HttpUtilities::CreateAuthorizationHeader(Settings->Token);
    
    ReceiveButtonState(false);
    
    HttpUtilities::SendGetRequest(Constants::API_PROGRAM_EQUIDISTANT, this, &UProgramMenu::OnEquidistantListResponse, &Header);
    HttpUtilities::SendGetRequest(Constants::API_PROGRAM_OCTOPUSG1, this, &UProgramMenu::OnOctopusG1ListResponse, &Header);
    HttpUtilities::SendGetRequest(Constants::API_PROGRAM_TRAINING, this, &UProgramMenu::OnTrainingListResponse, &Header);
    
    ReceiveMessage(*Constants::MESSAGE_CONNECTING);
    
    this->Settings = Settings;
}

void UProgramMenu::OnEquidistantListResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    Mutex.Lock();
    EquidistantListLoaded = true;
    FillComboBox(Request, Response, Successful, &EquidistantList);
    Mutex.Unlock();
}

void UProgramMenu::OnOctopusG1ListResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    Mutex.Lock();
    OctopusG1ListLoaded = true;
    FillComboBox(Request, Response, Successful, &OctopusG1List);
    Mutex.Unlock();
}

void UProgramMenu::OnTrainingListResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    Mutex.Lock();
    TrainingListLoaded = true;
    FillComboBox(Request, Response, Successful, &TrainingList);
    Mutex.Unlock();
}

void UProgramMenu::FillComboBox(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, TArray<FProgramShortInfo>* CurrentList)
{
    if (Successful && FJsonObjectConverter::JsonArrayStringToUStruct(Response->GetContentAsString(), CurrentList, 0, 0)) {
        ArrayUtilities::SortAscending(*CurrentList);
        
        if (EquidistantListLoaded && OctopusG1ListLoaded && TrainingListLoaded)
        {
            TArray<FString> ComboBoxStrings;
            
            for (FProgramShortInfo ProgramInfo : EquidistantList)
            {
                ComboBoxStrings.Add(FString::Printf(TEXT("%s%s"), *ProgramInfo.Name, *Constants::PROGRAM_LIST_EQUIDISTANT_SUFFIX));
            }
            for (FProgramShortInfo ProgramInfo : OctopusG1List)
            {
                ComboBoxStrings.Add(FString::Printf(TEXT("%s%s"), *ProgramInfo.Name,
                    *Constants::PROGRAM_LIST_OCTOPUSG1_SUFFIX));
            }
            for (FProgramShortInfo ProgramInfo : TrainingList)
            {
                ComboBoxStrings.Add(FString::Printf(TEXT("%s%s"), *ProgramInfo.Name,
                                                    *Constants::PROGRAM_LIST_TRAINING_SUFFIX));
            }
            
            ReceivePrograms(ComboBoxStrings);
            ReceiveMessage(TEXT(""));
            
            ReceiveButtonState(true);
        }
    }
    else
    {
        ReceiveMessage(*Constants::MESSAGE_CONNECTION_ERROR);
        ReceiveButtonState(true);
    }
}

void UProgramMenu::StartClicked(const FString SelectedProgramName)
{
    StartWasClicked = true;
    CalibrateWasClicked = false;
    GetProgramDetails(SelectedProgramName);
}

void UProgramMenu::CalibrateClicked(const FString SelectedProgramName)
{
    StartWasClicked = false;
    CalibrateWasClicked = true;
    GetProgramDetails(SelectedProgramName);
}

void UProgramMenu::GetProgramDetails(const FString SelectedProgramName)
{
    if (!SelectedProgramName.Equals(TEXT("")))
    {
        ReceiveButtonState(false);
        
        ReceiveMessage(*Constants::MESSAGE_CONNECTING);
        
        for (FProgramShortInfo ProgramInfo : EquidistantList)
        {
            FString ComboBoxName = FString::Printf(TEXT("%s%s"), *ProgramInfo.Name, *Constants::PROGRAM_LIST_EQUIDISTANT_SUFFIX);
            if (ComboBoxName.Equals(SelectedProgramName))
            {
                TMap<FString, FString> Header = HttpUtilities::CreateAuthorizationHeader(Settings->Token);
                HttpUtilities::SendGetRequest(FString::Printf(TEXT("%s%d/"), *Constants::API_PROGRAM_EQUIDISTANT, ProgramInfo.Id), this, &UProgramMenu::OnEquidistantDetailResponse, &Header);
            }
        }
        
        for (FProgramShortInfo ProgramInfo : OctopusG1List)
        {
            FString ComboBoxName = FString::Printf(TEXT("%s%s"), *ProgramInfo.Name, *Constants::PROGRAM_LIST_OCTOPUSG1_SUFFIX);
            if (ComboBoxName.Equals(SelectedProgramName))
            {
                TMap<FString, FString> Header = HttpUtilities::CreateAuthorizationHeader(Settings->Token);
                HttpUtilities::SendGetRequest(FString::Printf(TEXT("%s%d/"), *Constants::API_PROGRAM_OCTOPUSG1, ProgramInfo.Id), this, &UProgramMenu::OnOctopusG1DetailResponse, &Header);
            }
        }
        
        for (FProgramShortInfo ProgramInfo : TrainingList)
        {
            FString ComboBoxName = FString::Printf(TEXT("%s%s"), *ProgramInfo.Name, *Constants::PROGRAM_LIST_TRAINING_SUFFIX);
            if (ComboBoxName.Equals(SelectedProgramName)) {
                TMap<FString, FString> Header = HttpUtilities::CreateAuthorizationHeader(Settings->Token);
                HttpUtilities::SendGetRequest(FString::Printf(TEXT("%s%d/"), *Constants::API_PROGRAM_TRAINING, ProgramInfo.Id), this, &UProgramMenu::OnTrainingDetailResponse, &Header);
            }
        }
    }
    else
    {
        ReceiveMessage(*Constants::MESSAGE_SELECT_PROGRAM);
    }
}

void UProgramMenu::OnEquidistantDetailResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    FEquidistantProgram Program;
    
    if (Successful && FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Program, 0, 0)) {
        Program.PostProcessJsonInput();
        
        RemoveFromViewport();
        if (StartWasClicked)
        {
            EquidistantSelectedCallback.ExecuteIfBound(Program);
        }
        if (CalibrateWasClicked)
        {
            CalibrateCallback.ExecuteIfBound(Program);
        }
    }
    else
    {
        ReceiveMessage(*Constants::MESSAGE_CONNECTION_ERROR);
    }
    
    ReceiveButtonState(true);
}

void UProgramMenu::OnOctopusG1DetailResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    FOctopusG1Program Program;
    
    if (Successful && FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Program, 0, 0)) {
        Program.PostProcessJsonInput();
        
        RemoveFromViewport();
        if (StartWasClicked)
        {
            OctopusG1SelectedCallback.ExecuteIfBound(Program);
        }
        if (CalibrateWasClicked)
        {
            CalibrateCallback.ExecuteIfBound(Program);
        }
    }
    else
    {
        ReceiveMessage(*Constants::MESSAGE_CONNECTION_ERROR);
    }
    
    ReceiveButtonState(true);
}

void UProgramMenu::OnTrainingDetailResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
    FTrainingProgram Program;
    
    if (Successful && FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Program, 0, 0)) {
        Program.PostProcessJsonInput();
        
        RemoveFromViewport();        
        if (StartWasClicked)
        {
            TrainingSelectedCallback.ExecuteIfBound(Program);
        }
        if (CalibrateWasClicked)
        {
            CalibrateCallback.ExecuteIfBound(Program);
        }
    }
    else
    {
        ReceiveMessage(*Constants::MESSAGE_CONNECTION_ERROR);
    }
    
    ReceiveButtonState(true);
}

void UProgramMenu::LogoutClicked()
{
    Settings->Token = TEXT("");
    PersistencyUtilities::SaveSettings(Settings);
    
    RemoveFromViewport();
    LoggedOutCallback.ExecuteIfBound();
}


