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

#include "Constants.h"

#define ADD_WARNING(VAR) TEXT(VAR " (USED IN CPP - DO NOT CHANGE NAME)")


const int32 Constants::LEFT_EYE = 0;
const int32 Constants::RIGHT_EYE = 1;
const int32 Constants::BOTH_EYES = 2;

const float Constants::USER_HEIGHT = 180.0f;
const float Constants::MESH_RADIUS = 100.0f;
const float Constants::MESH_CALIBRATION_SCALING = 0.7f;
const float Constants::MESH_CALIBRATION_OFFSET = -50.0f;

const float Constants::FIXATION_POSITION_1[2] = {1.0f, 1.0f};
const float Constants::FIXATION_POSITION_2[2] = {1.0f, -1.0f};
const float Constants::FIXATION_POSITION_3[2] = {-1.0f, 1.0f};
const float Constants::FIXATION_POSITION_4[2] = {-1.0f, -1.0f};

// This position if from the books
// Harrington, Normal Visual Field. In: Mosby, The Visual Fields - A textbook and atlas of clinical perimetry. Saint Louis, C.V. Mosby Co. 1976:97-104.
// Traquair, The Normal Field of Vision. In: Kimpton, An introduction to Clinical Perimetry. London, Henry Kimpton. 1948:14-16.
// See also review paper
// Rhodes, A Systematic Review: What is the Normative Size of the Blind Spot Scotoma in Adults?, Ophthalmology Research: An International Journal 1(1): 51-66, 2013
const float Constants::BLIND_SPOT_LONGITUDE = 15.5f;
const float Constants::BLIND_SPOT_LATITUDE = -1.5f;

// These positions are from the paper
// C Messmer and J Flammer, Octopus Program G1X, Ophthalmologica 1991, 203:184-188
// Figure 2
const float Constants::OCTOPUS_G1_POSITIONS[59][2] = {
    {26.0f, -8.0f}, {26.0f, 8.0f},
    {20.0f, -20.0f}, {20.0f, -12.0f}, {20.0f, -4.0f}, {20.0f, 4.0f}, {20.0f, 12.0f}, {20.0f, 20.0f},
    {14.0f, -4.0f}, {14.0f, 4.0f},
    {12.0f, -20.0f}, {12.0f, -12.0f}, {12.0f, 12.0f}, {12.0f, 20.0f},
    {8.0f, -8.0f}, {8.0f, -2.0f}, {8.0f, 2.0f}, {8.0f, 8.0f}, {8.0f, 26.0f},
    {4.0f, -26.0f}, {4.0f, -20.0f}, {4.0f, -14.0f}, {4.0f, -4.0f}, {4.0f, 4.0f}, {4.0f, 22.0f},
    {2.0f, -8.0f}, {2.0f, -2.0f}, {2.0f, 2.0f}, {2.0f, 8.0f},
    {0.0f, 0.0f},
    {-2.0f, -8.0f}, {-2.0f, -2.0f}, {-2.0f, 2.0f}, {-2.0f, 8.0f},
    {-4.0f, -26.0f}, {-4.0f, -20.0f}, {-4.0f, -14.0f}, {-4.0f, -4.0f}, {-4.0f, 4.0f}, {-4.0f, 22.0f},
    {-8.0f, -8.0f}, {-8.0f, 8.0f}, {-8.0f, 26.0f},
    {-9.0f, -3.0f}, {-9.0f, 3.0f},
    {-12.0f, -20.0f}, {-12.0f, -12.0f}, {-12.0f, 12.0f}, {-12.0f, 20.0f},
    {-14.0f, -4.0f}, {-14.0f, 4.0f},
    {-20.0f, -20.0f}, {-20.0f, -12.0f}, {-20.0f, -4.0f}, {-20.0f, 4.0f}, {-20.0f, 12.0f}, {-20.0f, 20.0f},
    {-26.0f, -8.0f}, {-26.0f, 8.0f},
};

const FString Constants::SINGLE_EYE_MATERIAL_EYE_LABEL = ADD_WARNING("Eye");
const FString Constants::SINGLE_EYE_MATERIAL_COLOR_LABEL = ADD_WARNING("Color");

const FString Constants::SAVE_GAME_LABEL = TEXT("VFATSaveGame");
const int32 Constants::SAVE_GAME_INDEX = 0;

const FString Constants::BUTTON_PRESSED_LABEL = ADD_WARNING("BUTTON PRESSED");

const FString Constants::PROGRAM_LIST_EQUIDISTANT_SUFFIX = TEXT(" [Equidistant]");
const FString Constants::PROGRAM_LIST_OCTOPUSG1_SUFFIX = TEXT(" [Octopus G1-Based]");
const FString Constants::PROGRAM_LIST_TRAINING_SUFFIX = TEXT(" [Training]");

const FString Constants::CSV_SEPARATOR = FString(TEXT(";"));

//const FString Constants::SERVER_URL = TEXT("https://www.vfat.mad.tf.fau.de");
const FString Constants::SERVER_URL = TEXT("http://192.168.178.44:8000");

const FString Constants::HTTP_LINE_BREAK = TEXT("\r\n");

const FString Constants::HTTP_REQUEST_BOUNDARY_DEFINITION = TEXT("boundary123");;
const FString Constants::HTTP_REQUEST_BOUNDARY_TEXT = TEXT("--") + Constants::HTTP_REQUEST_BOUNDARY_DEFINITION;

const FString Constants::HTTP_REQUEST_HEADER_AUTHORIZAITON_LABEL = TEXT("Authorization");
const FString Constants::HTTP_REQUEST_HEADER_AUTHORIZATION_VALUE_PREFIX = TEXT("Token ");

const FString Constants::HTTP_REQUEST_CONTENT_TYPE_LABEL = TEXT("Content-Type");
const FString Constants::HTTP_REQUEST_CONTENT_TYPE_MULTIPART_FORM = FString::Printf(TEXT("multipart/form-data; boundary=%s"), *Constants::HTTP_REQUEST_BOUNDARY_DEFINITION);
const FString Constants::HTTP_REQUEST_CONTENT_LENGTH_LABEL = TEXT("Content-Length");
const FString Constants::HTTP_REQUEST_CONTENT_TYPE_CSV_LABEL = TEXT("Content-Type: text/csv");
const FString Constants::HTTP_REQUEST_CONTENT_DISPOSITION_LABEL_PREFIX = TEXT("Content-Disposition: form-data; name=");

const FString Constants::HTTP_REQUEST_FILE_FIELD_LABEL = TEXT("file");
const FString Constants::HTTP_REQUEST_DURATION_FIELD_LABEL = TEXT("duration");
const FString Constants::HTTP_REQUEST_FALSE_POSITIVES_FIELD_LABEL = TEXT("false_positive");
const FString Constants::HTTP_REQUEST_EYE_FIELD_LABEL = TEXT("tested_eye");
const FString Constants::HTTP_REQUEST_CONFIGURATION_FIELD_LABEL = TEXT("configuration");
const FString Constants::HTTP_REQUEST_BLIND_SPOT_FALSE_POSITIVES_FIELD_LABEL = TEXT("blind_spot_false_positive");

const FString Constants::API_TOKEN = FString::Printf(TEXT("%s/api/v1/token/"), *Constants::SERVER_URL);
const FString Constants::API_TOKEN_RESPONSE_FIELD = TEXT("token");

const FString Constants::API_PROGRAM_EQUIDISTANT = FString::Printf(TEXT("%s/api/v1/program/equidistant/"), *Constants::SERVER_URL);
const FString Constants::API_PROGRAM_OCTOPUSG1 = FString::Printf(TEXT("%s/api/v1/program/octopusg1/"), *Constants::SERVER_URL);
const FString Constants::API_PROGRAM_TRAINING = FString::Printf(TEXT("%s/api/v1/program/training/"), *Constants::SERVER_URL);

const FString Constants::API_UPLOAD_EQUIDISTANT = FString::Printf(TEXT("%s/api/v1/assessment/equidistant/"), *Constants::SERVER_URL);
const FString Constants::API_UPLOAD_OCTOPUSG1 = FString::Printf(TEXT("%s/api/v1/assessment/octopusg1/"), *Constants::SERVER_URL);

const FString Constants::MESSAGE_CONNECTING = TEXT("Contacting server...");
const FString Constants::MESSAGE_CONNECTION_ERROR = TEXT("Connection error!");
const FString Constants::MESSAGE_INVALID_CREDENTIALS = TEXT("Invalid credentials!");
const FString Constants::MESSAGE_UPLOADING = TEXT("Uploading result...");
const FString Constants::MESSAGE_SELECT_PROGRAM = TEXT("Please select a program!");


