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
#include "Runtime/Online/HTTP/Public/Http.h"

#include "Constants.h"


class HttpUtilities
{
public:
    template<typename T1, typename T2>
    static void SendGetRequest(const FString& URL, T1 CallbackObject, T2 CallbackFunction, const TMap<FString, FString>* const HeaderFields = nullptr, const TMap<FString, FString>* const FormFields = nullptr, const TMap<FString, FString>* const TextFiles = nullptr);
    
    template<typename T1, typename T2>
    static void SendPostRequest(const FString& URL, T1 CallbackObject, T2 CallbackFunction, const TMap<FString, FString>* const HeaderFields = nullptr, const TMap<FString, FString>* const FormFields = nullptr, const TMap<FString, FString>* const TextFiles = nullptr);
    
    template<typename T1, typename T2>
    static void SendRequest(const FString& URL, const FString& Verb, T1 CallbackObject, T2 CallbackFunction, const TMap<FString, FString>* const HeaderFields = nullptr, const TMap<FString, FString>* const FormFields = nullptr, const TMap<FString, FString>* const TextFiles = nullptr);
    
    static TMap<FString, FString> CreateAuthorizationHeader(const FString Token);
};


template<typename T1, typename T2>
void HttpUtilities::SendGetRequest(const FString& URL, T1 CallbackObject, T2 CallbackFunction, const TMap<FString, FString>* const HeaderFields, const TMap<FString, FString>* const FormFields, const TMap<FString, FString>* const TextFiles)
{
    HttpUtilities::SendRequest(URL, TEXT("GET"), CallbackObject, CallbackFunction, HeaderFields, FormFields, TextFiles);
}

template<typename T1, typename T2>
void HttpUtilities::SendPostRequest(const FString& URL, T1 CallbackObject, T2 CallbackFunction, const TMap<FString, FString>* const HeaderFields, const TMap<FString, FString>* const FormFields, const TMap<FString, FString>* const TextFiles)
{
    HttpUtilities::SendRequest(URL, TEXT("POST"), CallbackObject, CallbackFunction, HeaderFields, FormFields, TextFiles);
}

template<typename T1, typename T2>
void HttpUtilities::SendRequest(const FString& URL, const FString& Verb, T1 CallbackObject, T2 CallbackFunction, const TMap<FString, FString>* const HeaderFields, const TMap<FString, FString>* const FormFields, const TMap<FString, FString>* const TextFiles)
{
    FString Body = TEXT("");
    FHttpModule* HttpModule = &FHttpModule::Get();;
    TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
    
    Request->SetURL(URL);
    Request->SetVerb(Verb);
    
    if (HeaderFields && HeaderFields->Num() > 0)
    {
        for (auto& Element: *HeaderFields)
        {
            Request->SetHeader(*Element.Key, *Element.Value);
        }
    }
    
    if (FormFields && FormFields->Num() > 0)
    {
        for (auto& Element: *FormFields)
        {
            Body += Constants::HTTP_REQUEST_BOUNDARY_TEXT + Constants::HTTP_LINE_BREAK + Constants::HTTP_REQUEST_CONTENT_DISPOSITION_LABEL_PREFIX +
            FString::Printf(TEXT("\"%s\""), *Element.Key) + Constants::HTTP_LINE_BREAK + Constants::HTTP_LINE_BREAK + *Element.Value + Constants::HTTP_LINE_BREAK;
        }
        Request->SetHeader(Constants::HTTP_REQUEST_CONTENT_TYPE_LABEL, Constants::HTTP_REQUEST_CONTENT_TYPE_MULTIPART_FORM);
    }
    
    if (TextFiles && TextFiles->Num() > 0)
    {
        for (auto& Element: *TextFiles)
        {
            Body += Constants::HTTP_REQUEST_BOUNDARY_TEXT + Constants::HTTP_LINE_BREAK + Constants::HTTP_REQUEST_CONTENT_DISPOSITION_LABEL_PREFIX +
            FString::Printf(TEXT("\"%s\"; filename=\"%s.csv\""), *Element.Key, *Element.Key) + Constants::HTTP_LINE_BREAK + Constants::HTTP_REQUEST_CONTENT_TYPE_CSV_LABEL + Constants::HTTP_LINE_BREAK + Constants::HTTP_LINE_BREAK + *Element.Value + Constants::HTTP_LINE_BREAK;
        }
        Request->SetHeader(Constants::HTTP_REQUEST_CONTENT_TYPE_LABEL, Constants::HTTP_REQUEST_CONTENT_TYPE_MULTIPART_FORM);
    }
    
    if (Body.Len() > 0)
    {
        Body += Constants::HTTP_REQUEST_BOUNDARY_TEXT + Constants::HTTP_LINE_BREAK;
    }
    
    Request->SetHeader(Constants::HTTP_REQUEST_CONTENT_LENGTH_LABEL, FString::FromInt(Body.Len()));
    Request->SetContentAsString(Body);
    
    Request->OnProcessRequestComplete().BindUObject(CallbackObject, CallbackFunction);
    Request->ProcessRequest();
}

