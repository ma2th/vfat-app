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

#include "OctopusG1Position.h"


void UOctopusG1Position::Init(int32 NumThresholds, float Longitude, float Latitude, int32 Eye)
{
    UVisualFieldPosition::Init(NumThresholds, Longitude, Latitude, Eye);
    
    StepSize = 4;
    SkipLastMinusOne = false;
    LastValidIndex = NumThresholds - 1;
}

void UOctopusG1Position::SetCurrentThresholdResult(bool Correct)
{
    if (CurrentIndex != POSITION_FINISHED) // safety check
    {
        if (Correct)
        {
            DetectedIndex = CurrentIndex;
            
            if (CurrentIndex == 0)
            {
                CurrentIndex = POSITION_FINISHED;
            }
            else
            {
                if (StepSize == 4) {
                    StepSize = -2;
                }
                else if (StepSize == -2)
                {
                    if (SkipLastMinusOne)
                    {
                        CurrentIndex = POSITION_FINISHED;
                    }
                    else
                    {
                        StepSize = -1;
                    }
                }
                else if (StepSize == -1 || StepSize == 1)
                {
                    CurrentIndex = POSITION_FINISHED;
                }
            }
        }
        else
        {
            if (CurrentIndex == LastValidIndex)
            {
                CurrentIndex = POSITION_FINISHED;
                DetectedIndex = NO_THRESHOLD_FOUND;
            }
            else if (CurrentIndex < LastValidIndex)
            {
                if (StepSize == -2)
                {
                    StepSize = 1;
                }
                else if (StepSize == -1 || StepSize == 1)
                {
                    CurrentIndex = POSITION_FINISHED;
                }
            }
        }
        
        // In case there is only one threshold,
        // this if will never be true so that this
        // case does not required special consideration
        // inside the if
        if (CurrentIndex != POSITION_FINISHED) {
            CurrentIndex = CurrentIndex + StepSize;
            
            // LastValidIndex has to be a multiple of 4
            // If LastValidIndex mod 4 != 0, these special
            // situations have to be handled.
            if (CurrentIndex > LastValidIndex)
            {
                CurrentIndex = LastValidIndex;
                if (LastValidIndex % 4 == 1)
                {
                    StepSize = 1;
                }
                else if (LastValidIndex % 4 == 2)
                {
                    StepSize = -2;
                }
                else if (LastValidIndex % 4 == 3)
                {
                    SkipLastMinusOne = true;
                }
            }
        }
    }
}

