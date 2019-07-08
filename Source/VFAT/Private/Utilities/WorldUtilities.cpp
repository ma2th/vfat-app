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

#include "WorldUtilities.h"

#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"

#include "Constants.h"
#include "MathUtilities.h"


void WorldUtilities::SetupGoogleVRRuntime(UWorld* World, UCameraComponent* VRCamera)
{
    UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
    UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
    
    VRCamera->SetRelativeLocation(FVector(0.0f, 0.0f, Constants::USER_HEIGHT));
    
    FString Command = FString::Printf(TEXT("vr.bEnableStereo True"));
    World->Exec(World, *Command);
}

void WorldUtilities::ShowErrorAndQuit(const FString& Message, UWorld* World)
{
    FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Internal error (%s)!"), *Message)));
    // <= 4.19
    // UKismetSystemLibrary::QuitGame(World, World->GetFirstPlayerController(), EQuitPreference::Quit);
    // > 4.19
    UKismetSystemLibrary::QuitGame(World, World->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void WorldUtilities::MoveComponent(USceneComponent* Component, float Longitude, float Latitude, float Radius)
{
    float X, Y, Z;
    FRotator Rotation;
    FVector Location;
    FVector Gradient;
    
    MathUtilities::GeographicToCartesian(Longitude, Latitude, Radius, X, Y, Z);
    
    Location.X = X;
    Location.Y = Y;
    Location.Z = Z;
    
    // Rotate object so that it faces observer
    Gradient.X = 2.0f * Location.X;
    Gradient.Y = 2.0f * Location.Y;
    Gradient.Z = 2.0f * Location.Z;
    Rotation = Gradient.Rotation();
    
    Component->SetRelativeLocation(Location);
    Component->SetRelativeRotation(Rotation);
}
