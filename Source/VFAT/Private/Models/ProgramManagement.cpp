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


#include "ProgramManagement.h"

#include "Utilities/ArrayUtilities.h"


bool FProgramShortInfo::operator<(const FProgramShortInfo& Other) const
{
    return Name < Other.Name;
}

void FAbstractProgram::PostProcessJsonInput()
{
    TArray<FString> Splitted;
    
    Thresholds.ParseIntoArray(Splitted, TEXT(" "), true);
    
    ThresholdsAsArray.Empty();
    for (FString Value : Splitted)
    {
        ThresholdsAsArray.Add(FCString::Atof(*Value));
    }
    
    ArrayUtilities::SortDescending(ThresholdsAsArray);
}
