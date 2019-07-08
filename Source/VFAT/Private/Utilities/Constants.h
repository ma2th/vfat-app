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


class Constants
{
public:
    static const int32 LEFT_EYE;
    static const int32 RIGHT_EYE;
    static const int32 BOTH_EYES;
    
    static const float USER_HEIGHT;
    static const float MESH_RADIUS;
    static const float MESH_CALIBRATION_SCALING;
    static const float MESH_CALIBRATION_OFFSET;
    
    static const float FIXATION_POSITION_1[2];
    static const float FIXATION_POSITION_2[2];
    static const float FIXATION_POSITION_3[2];
    static const float FIXATION_POSITION_4[2];
    
    static const float BLIND_SPOT_LONGITUDE;
    static const float BLIND_SPOT_LATITUDE;
    static const float OCTOPUS_G1_POSITIONS[59][2];
    
    static const FString SINGLE_EYE_MATERIAL_COLOR_LABEL;
    static const FString SINGLE_EYE_MATERIAL_EYE_LABEL;
    
    static const FString SAVE_GAME_LABEL;
    static const int32 SAVE_GAME_INDEX;
    
    static const FString BUTTON_PRESSED_LABEL;
    
    static const FString PROGRAM_LIST_EQUIDISTANT_SUFFIX;
    static const FString PROGRAM_LIST_OCTOPUSG1_SUFFIX;
    static const FString PROGRAM_LIST_TRAINING_SUFFIX;
    
    static const FString CSV_SEPARATOR;
    
    static const FString SERVER_URL;

    static const FString HTTP_LINE_BREAK;
    static const FString HTTP_REQUEST_BOUNDARY_DEFINITION;
    static const FString HTTP_REQUEST_BOUNDARY_TEXT;
    
    static const FString HTTP_REQUEST_HEADER_AUTHORIZAITON_LABEL;
    static const FString HTTP_REQUEST_HEADER_AUTHORIZATION_VALUE_PREFIX;
    
    static const FString HTTP_REQUEST_CONTENT_LENGTH_LABEL;
    static const FString HTTP_REQUEST_CONTENT_TYPE_LABEL;
    static const FString HTTP_REQUEST_CONTENT_TYPE_MULTIPART_FORM;
    static const FString HTTP_REQUEST_CONTENT_TYPE_CSV_LABEL;
    static const FString HTTP_REQUEST_CONTENT_DISPOSITION_LABEL_PREFIX;
    
    static const FString HTTP_REQUEST_FILE_FIELD_LABEL;
    static const FString HTTP_REQUEST_DURATION_FIELD_LABEL;
    static const FString HTTP_REQUEST_FALSE_POSITIVES_FIELD_LABEL;
    static const FString HTTP_REQUEST_EYE_FIELD_LABEL;
    static const FString HTTP_REQUEST_CONFIGURATION_FIELD_LABEL;
    static const FString HTTP_REQUEST_BLIND_SPOT_FALSE_POSITIVES_FIELD_LABEL;
    
    static const FString API_TOKEN;
    static const FString API_TOKEN_RESPONSE_FIELD;
    static const FString API_PROGRAM_EQUIDISTANT;
    static const FString API_PROGRAM_OCTOPUSG1;
    static const FString API_PROGRAM_TRAINING;
    static const FString API_UPLOAD_EQUIDISTANT;
    static const FString API_UPLOAD_OCTOPUSG1;
    
    static const FString MESSAGE_CONNECTING;
    static const FString MESSAGE_CONNECTION_ERROR;
    static const FString MESSAGE_INVALID_CREDENTIALS;
    static const FString MESSAGE_UPLOADING;
    static const FString MESSAGE_SELECT_PROGRAM;
};
