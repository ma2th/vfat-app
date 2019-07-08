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

#include "VisualField.h"


void UVisualField::Reset()
{
    CurrentPosition = -1;
    Positions.Empty();
}

bool UVisualField::HasMoreUntestedPositions()
{
    for (int PositionIndex = 0; PositionIndex < Positions.Num(); PositionIndex++)
    {
        if (Positions[PositionIndex]->NextUntestedThresholdIndex() != UVisualFieldPosition::NO_THRESHOLD_FOUND)
        {
            return true;
        }
    }
    return false;
}

void UVisualField::NextUntestedPosition(float& OutLongitude, float& OutLatitude, int32& OutThresholdIndex, int32& OutEye)
{
    TArray<int32> PositionIndices;
    TArray<int32> ThresholdIndices;
    
    FindUntestedPositions(PositionIndices, ThresholdIndices);
    if (PositionIndices.Num() > 0)
    {
        int32 RandomPosition = FMath::RoundToInt(FMath::FRand() * (PositionIndices.Num() - 1));
        CurrentPosition = PositionIndices[RandomPosition];
        
        OutLongitude = Positions[CurrentPosition]->GetLongitude();
        OutLatitude = Positions[CurrentPosition]->GetLatitude();
        OutEye = Positions[CurrentPosition]->GetEye();
        OutThresholdIndex = Positions[CurrentPosition]->NextUntestedThresholdIndex();
        OutThresholdIndex = ThresholdIndices[RandomPosition];
        
        UE_LOG(LogTemp, Log, TEXT("Position %d, ThresholdIndex %d, Eye %d"), CurrentPosition, OutThresholdIndex, OutEye);
    }
    else
    {
        OutLongitude = -1;
        OutLatitude = -1;
        OutThresholdIndex = -1;
        OutEye = -1;
    }
}

void UVisualField::LastPositionWasDetected()
{
    if (CurrentPosition != -1)
    {
        Positions[CurrentPosition]->SetCurrentThresholdResult(true);
        CurrentPosition = -1;
    }
}

void UVisualField::LastPositionWasNotDetected()
{
    if (CurrentPosition != -1)
    {
        Positions[CurrentPosition]->SetCurrentThresholdResult(false);
        CurrentPosition = -1;
    }
}

int32 UVisualField::NumTestPositions()
{
    return Positions.Num();
}

FString UVisualField::ResultAsCSVString()
{
    FString Result = TEXT("");
    
    for (int PositionIndex = 0; PositionIndex < Positions.Num(); PositionIndex++)
    {
        float ThresholdValue = -1.0f;
        
        UVisualFieldPosition* Position = Positions[PositionIndex];
        int ThresholdIndex = Position->FirstDetectedThresholdIndex();
        
        if (ThresholdIndex != UVisualFieldPosition::NO_THRESHOLD_FOUND)
        {
            ThresholdValue = GetThresholdValue(ThresholdIndex);
        }
        
        Result += FString::SanitizeFloat(Position->GetLongitude()) + Constants::CSV_SEPARATOR
        + FString::SanitizeFloat(Position->GetLatitude()) + Constants::CSV_SEPARATOR
        + FString::SanitizeFloat(Constants::MESH_RADIUS) + Constants::CSV_SEPARATOR
        + FString::SanitizeFloat(ThresholdValue) + Constants::CSV_SEPARATOR
        + LINE_TERMINATOR;
    }
    
    return Result;
}

void UVisualField::FindUntestedPositions(TArray<int32>& PositionIndices, TArray<int32>& ThresholdIndices)
{
    PositionIndices.Empty();
    ThresholdIndices.Empty();
    
    for (int PositionIndex = 0; PositionIndex < Positions.Num(); PositionIndex++)
    {
        int ThresholdIndex = Positions[PositionIndex]->NextUntestedThresholdIndex();
        if (ThresholdIndex != UVisualFieldPosition::NO_THRESHOLD_FOUND)
        {
            PositionIndices.Add(PositionIndex);
            ThresholdIndices.Add(ThresholdIndex);
        }
    }
}
