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

#include "OctopusG1Field.h"

#include "Utilities/Constants.h"


void UOctopusG1Field::Init(FOctopusG1Program Program)
{
    this->Program = Program;
    Reset();
}

float UOctopusG1Field::GetThresholdValue(int32 Index)
{
    return Program.ThresholdsAsArray[Index];
}

void UOctopusG1Field::Reset()
{
    UVisualField::Reset();

    for (int i = 0; i < 59; i++)
    {
        float Latitude = Constants::OCTOPUS_G1_POSITIONS[i][0];
        float Longitude = Constants::OCTOPUS_G1_POSITIONS[i][1];
        
        if (this->Program.Eye == Constants::LEFT_EYE)
        {
            Longitude = Longitude * -1.0f;
        }

        UOctopusG1Position* Position = NewObject<UOctopusG1Position>(this);
        Position->Init(this->Program.ThresholdsAsArray.Num(), Longitude, Latitude, this->Program.Eye);

        Positions.Add(Position);
    }
}
