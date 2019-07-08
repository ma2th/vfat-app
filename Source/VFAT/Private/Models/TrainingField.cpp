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

#include "TrainingField.h"


void UTrainingField::Init(FTrainingProgram Program)
{
    this->Program = Program;
    Reset();
}

float UTrainingField::GetThresholdValue(int32 Index)
{
    return Program.ThresholdsAsArray[Index];
}

void UTrainingField::Reset()
{
    UVisualField::Reset();
    
    for (FCoordinate Coordinate : Program.Coordinates)
    {
        UTrainingPosition* Position = NewObject<UTrainingPosition>(this);
        
        Position->Init(this->Program.ThresholdsAsArray.Num(), Coordinate.Longitude,
                       Coordinate.Latitude, this->Program.Eye);
        if (this->Program.Reinforcement)
        {
            Position->ActivateReinforcement();
        }
        
        Positions.Add(Position);
    }
}
