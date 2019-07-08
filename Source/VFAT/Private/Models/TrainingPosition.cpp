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

#include "TrainingPosition.h"
#include "Utilities/Constants.h"


void UTrainingPosition::Init(int32 NumThresholds, float Longitude, float Latitude, int32 Eye)
{
    UVisualFieldPosition::Init(NumThresholds, Longitude, Latitude, Eye);
    
    this->ActivateBothEyes = false;
    this->UseReinforcement = false;
}

void UTrainingPosition::ActivateReinforcement()
{
    this->UseReinforcement = true;
}

void UTrainingPosition::SetCurrentThresholdResult(bool Value)
{
    if (CurrentIndex != POSITION_FINISHED) // safety check
    {
        if (Value)
        {
            DetectedIndex = CurrentIndex;
            CurrentIndex = POSITION_FINISHED;
        }
        else
        {
            if (UseReinforcement)
            {
                if (!ActivateBothEyes)
                {
                    ActivateBothEyes = true;
                }
                else
                {
                    ActivateBothEyes = false;
                    if (CurrentIndex == NumThresholds - 1)
                    {
                        CurrentIndex = POSITION_FINISHED;
                    }
                    else
                    {
                        CurrentIndex++;
                    }
                }
            }
            else
            {
                if (CurrentIndex == NumThresholds - 1)
                {
                    CurrentIndex = POSITION_FINISHED;
                }
                else
                {
                    CurrentIndex++;
                }
            }
        }
    }
}

int32 UTrainingPosition::GetEye()
{
    int32 StandardEye = UVisualFieldPosition::GetEye();
    
    if (UseReinforcement)
    {
        return ActivateBothEyes ? Constants::BOTH_EYES : StandardEye;
    }
    else
    {
        return StandardEye;
    }
}
