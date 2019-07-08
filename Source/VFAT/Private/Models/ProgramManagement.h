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
#include "ProgramManagement.generated.h"


USTRUCT()
struct FProgramShortInfo
{
    GENERATED_BODY()
    
    UPROPERTY()
    int32 Id;
    
    UPROPERTY()
    FString Name;
    
    bool operator<(const FProgramShortInfo& Other) const;
};

USTRUCT()
struct FAbstractProgram
{
    GENERATED_BODY()
    
    UPROPERTY()
    int32 Id;
    
    UPROPERTY()
    FString Name;
    
    UPROPERTY()
    FString Fixation_Color;
    
    UPROPERTY()
    FString Assessment_Color;
    
    UPROPERTY()
    int32 Eye;
    
    UPROPERTY()
    float Max_Waiting_Time;
    
    UPROPERTY()
    float Min_Waiting_Time;
    
    UPROPERTY()
    float Max_Response_Time;
    
    UPROPERTY()
    float Min_Response_Time;
    
    UPROPERTY()
    float Display_Time;
    
    UPROPERTY()
    float Stimulus_Size;
    
    UPROPERTY()
    FString Thresholds;
    
    UPROPERTY()
    TArray<float> ThresholdsAsArray;
    
    void PostProcessJsonInput();
};

USTRUCT()
struct FAssessmentProgram : public FAbstractProgram
{
    GENERATED_BODY()
    
    UPROPERTY()
    int32 Blind_Spot_Tests;
};

/**
 * The assumed spherical coordinate system is aligned so that its z-axis
 * is identical to the gaze direction of the Pawn. The inclination angle,
 * therefore, defines "visual eccentricity".
 **/
USTRUCT()
struct FEquidistantProgram : public FAssessmentProgram
{
    GENERATED_BODY()
    
    UPROPERTY()
    int32 Test_Positions;
    
    UPROPERTY()
    float Max_Inclination;
    
    UPROPERTY()
    float Min_Inclination;
};

USTRUCT()
struct FOctopusG1Program : public FAssessmentProgram
{
    GENERATED_BODY()
};

USTRUCT()
struct FCoordinate
{
    GENERATED_BODY()
    
    UPROPERTY()
    float Longitude;
    
    UPROPERTY()
    float Latitude;
    
    UPROPERTY()
    float Radius;
};

USTRUCT()
struct FTrainingProgram : public FAbstractProgram
{
    GENERATED_BODY()
    
    UPROPERTY()
    bool Random_Training_Color;
    
    UPROPERTY()
    bool Reinforcement;
    
    UPROPERTY()
    TArray<FCoordinate> Coordinates;
};
