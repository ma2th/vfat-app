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

#include "VisualFieldPosition.h"


const int32 UVisualFieldPosition::NO_THRESHOLD_FOUND = -1;

const int32 UVisualFieldPosition::POSITION_FINISHED = -1;

void UVisualFieldPosition::Init(int32 NumThresholds, float Longitude, float Latitude, int32 Eye)
{
    this->Latitude = Latitude;
    this->Longitude = Longitude;
    this->NumThresholds = NumThresholds;
    this->Eye = Eye;
    
    CurrentIndex = 0;
    DetectedIndex = NO_THRESHOLD_FOUND;
}

int32 UVisualFieldPosition::FirstDetectedThresholdIndex()
{
    return DetectedIndex;
}

int32 UVisualFieldPosition::NextUntestedThresholdIndex()
{
    if (CurrentIndex != POSITION_FINISHED)
    {
        return CurrentIndex;
    }
    else
    {
        return NO_THRESHOLD_FOUND;
    }
}

float UVisualFieldPosition::GetLongitude()
{
    return Longitude;
}

float UVisualFieldPosition::GetLatitude()
{
    return Latitude;
}

int32 UVisualFieldPosition::GetNumThresholds()
{
    return NumThresholds;
}

int32 UVisualFieldPosition::GetEye()
{
    return Eye;
}
