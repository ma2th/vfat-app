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

#include "SingleEyeComponent.h"

#include "Engine/StaticMesh.h"

#include "Utilities/Constants.h"
#include "Utilities/MathUtilities.h"
#include "Utilities/WorldUtilities.h"


void USingleEyeComponent::SetupMaterial(UMaterialInterface* Material)
{
    MaterialInstance = CreateAndSetMaterialInstanceDynamicFromMaterial(0, Material);
}

void USingleEyeComponent::ActivateProgramMode(FAbstractProgram Program, bool IsFixationComponent, bool RandomColor)
{
    float SizeInRad = MathUtilities::DegreeToRad(Program.Stimulus_Size);
    float MeshRadius = GetStaticMesh()->GetBounds().SphereRadius;
    float ScalingFactor = (FGenericPlatformMath::Tan(SizeInRad / 2.0f) * Constants::MESH_RADIUS) / MeshRadius;
    
    if (IsFixationComponent)
    {
        SetColor(FColor::FromHex(Program.Fixation_Color));
        SetEye(Program.Eye);
        SetVisibility(true);
    }
    else
    {
        SetColor(FColor::FromHex(Program.Assessment_Color));
        SetEye(Program.Eye);
        SetVisibility(false);
    }
    SetRelativeScale3D(FVector(ScalingFactor));
    
    this->Program = Program;
    this->RandomColor = RandomColor;
}

void USingleEyeComponent::ActivateCalibrationMode(FAbstractProgram Program, bool IsFixationComponent)
{
    if (IsFixationComponent)
    {
        SetColor(FColor::FromHex(Program.Fixation_Color));
    }
    else
    {
        SetColor(FColor::FromHex(Program.Assessment_Color));
    }
    SetEye(Constants::BOTH_EYES);
    
    SetRelativeScale3D(FVector(Constants::MESH_CALIBRATION_SCALING));
    SetRelativeLocation(FVector(Constants::MESH_RADIUS, 0.0f, Constants::MESH_CALIBRATION_OFFSET));
    SetVisibility(false);
    
    this->Program = Program;
    this->RandomColor = false;
}

void USingleEyeComponent::MoveToBlindSpot()
{
    if (Program.Eye == Constants::LEFT_EYE)
    {
        WorldUtilities::MoveComponent(this, -1.0f * Constants::BLIND_SPOT_LONGITUDE, Constants::BLIND_SPOT_LATITUDE, Constants::MESH_RADIUS);
        SetThresholdAndEye(Program.ThresholdsAsArray.Num() / 2, Program.Eye);
    }
    else
    {
        WorldUtilities::MoveComponent(this, Constants::BLIND_SPOT_LONGITUDE, Constants::BLIND_SPOT_LATITUDE, Constants::MESH_RADIUS);
        SetThresholdAndEye(Program.ThresholdsAsArray.Num() / 2, Program.Eye);
    }
}

void USingleEyeComponent::MoveToCenter()
{
    WorldUtilities::MoveComponent(this, 0.0f, 0.0f, Constants::MESH_RADIUS);
    SetThresholdAndEye(Program.ThresholdsAsArray.Num() - 1, Program.Eye);
}

void USingleEyeComponent::SetThresholdAndEye(int32 ThresholdIndex, int32 Eye)
{
    SetThreshold(ThresholdIndex);
    SetEye(Eye);
}

void USingleEyeComponent::SetThreshold(int32 ThresholdIndex)
{
    // Threshold in db = 10 * log (reference luminance / (stimulus luminance - background luminance))
    // Reference luminance is maximum luminiance, which is 1.0f in RGB
    // Background luminance is assumed to be black, which is 0.0f in RGB
    // -> Threshold in db = 10 * log (1.0f / stimulus luminance in RGB)
    // -> Stimulus luminance in RGB = 10 ^ (- (threshold in dB / 10))

    FLinearColor CurrentBaseColor = BaseColor;
    if (RandomColor)
    {
        float Random = FMath::FRand();
        if (Random < 1.0f / 3.0f)
        {
            CurrentBaseColor = FLinearColor::Red;
        }
        else if (Random < 2.0f / 3.0f)
        {
            CurrentBaseColor = FLinearColor::Green;
        }
        else
        {
            CurrentBaseColor = FLinearColor::Blue;
        }
    }
    
    float Threshold = Program.ThresholdsAsArray[ThresholdIndex];
    const float Alpha = FGenericPlatformMath::Pow(10.0f, -(Threshold / 10.0f));
    FLinearColor Color = FMath::Lerp(FLinearColor::Black, CurrentBaseColor, Alpha);
    Color.A = 1.0f;
    
    MaterialInstance->SetVectorParameterValue(FName(*Constants::SINGLE_EYE_MATERIAL_COLOR_LABEL), Color);
}

void USingleEyeComponent::SetEye(int32 Eye)
{
    MaterialInstance->SetScalarParameterValue(FName(*Constants::SINGLE_EYE_MATERIAL_EYE_LABEL), Eye);
}

void USingleEyeComponent::SetColor(FLinearColor Color)
{
    MaterialInstance->SetVectorParameterValue(FName(*Constants::SINGLE_EYE_MATERIAL_COLOR_LABEL), Color);
    this->BaseColor = Color;
}
