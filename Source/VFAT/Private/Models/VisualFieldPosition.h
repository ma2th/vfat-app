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
#include "VisualFieldPosition.generated.h"

UCLASS()
class UVisualFieldPosition : public UObject
{
    GENERATED_BODY()
    
public:
    static const int32 NO_THRESHOLD_FOUND;
    
    virtual void Init(int32 NumThresholds, float Longitude, float Latitude, int32 Eye);
    
    virtual void SetCurrentThresholdResult(bool Value) PURE_VIRTUAL(UVisualFieldPosition::SetCurrentThresholdResult, ;);
    
    virtual int32 GetEye();
    
    float GetLongitude();
    
    float GetLatitude();
    
    int32 GetNumThresholds();
    
    int32 FirstDetectedThresholdIndex();
    
    int32 NextUntestedThresholdIndex();
    
protected:
    static const int32 POSITION_FINISHED;
    
    float Longitude;
    
    float Latitude;
    
    int32 Eye;
    
    int32 NumThresholds;
    
    int32 CurrentIndex;
    
    int32 DetectedIndex;
};
