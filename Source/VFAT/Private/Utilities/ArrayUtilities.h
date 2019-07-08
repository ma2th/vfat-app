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


class ArrayUtilities
{
public:
    template<typename T>
    static void Shuffle(TArray<T>& Array);
    
    template<typename T>
    static void SortAscending(TArray<T>& Array);
    
    template<typename T>
    static void SortDescending(TArray<T>& Array);
};


template<typename T>
void ArrayUtilities::Shuffle(TArray<T>& Array)
{
    for (int32 i = 0; i < Array.Num(); i++) {
        int32 j = FMath::FloorToInt(FMath::FRand() * (Array.Num() - 1));
        
        T Temp = Array[i];
        Array[i] = Array[j];
        Array[j] = Temp;
    }
}

template<typename T>
void ArrayUtilities::SortAscending(TArray<T>& Array)
{
    Array.Sort([](const T A, const T B) {
        if (A < B)
        {
            return true;
        }
        return false;
    });
}

template<typename T>
void ArrayUtilities::SortDescending(TArray<T>& Array)
{
    Array.Sort([](const T A, const T B) {
        if (A > B)
        {
            return true;
        }
        return false;
    });
}
