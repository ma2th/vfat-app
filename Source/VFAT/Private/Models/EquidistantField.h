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
#include "UObject/NoExportTypes.h"

#include "VisualField.h"
#include "ProgramManagement.h"
#include "EquidistantPosition.h"

#include "EquidistantField.generated.h"


UCLASS()
class UEquidistantField : public UVisualField
{
	GENERATED_BODY()

public:
    void Init(FEquidistantProgram Program);
    
protected:
    virtual void Reset() override;
    
    virtual float GetThresholdValue(int32 Index) override;
    
private:
    bool CheckPosition(float Longitude, float Latitude);
    
    FEquidistantProgram Program;
};
