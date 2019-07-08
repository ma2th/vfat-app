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
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Misc/MessageDialog.h"


class WorldUtilities
{
public:
    static void SetupGoogleVRRuntime(UWorld* World, UCameraComponent* VRCamera);
    
    static void ShowErrorAndQuit(const FString& Message, UWorld* World);
    
    static void MoveComponent(USceneComponent* Component, float Longitude, float Latitude, float Radius);
    
    template<typename T>
    static T* CreateMenu(UWorld* World, UClass* MenuClass);
    
    template<typename T>
    static T* GetSceneComponent(const AActor* const Actor, const FString& Name);
};


template<typename T>
T* WorldUtilities::CreateMenu(UWorld* World, UClass* MenuClass)
{
    T* Menu;
    APlayerController* Controller = World->GetFirstPlayerController();
    
    if (MenuClass)
    {
        // <= 4.19
        // Menu = Cast<T>(UUserWidget::CreateWidgetOfClass(MenuClass, World->GetGameInstance(), World, Controller));
        // > 4.19
        Menu = Cast<T>(UUserWidget::CreateWidgetInstance(*World->GetGameInstance(), MenuClass, MenuClass->GetDefaultObjectName()));
        
        return Menu;
    }
    return nullptr;
}

template<typename T>
T* WorldUtilities::GetSceneComponent(const AActor* const Actor, const FString& Name)
{
    TSet<UActorComponent*> Components = Actor->GetComponents();
    for (auto Component : Components)
    {
        if (Component->GetName().Equals(Name))
        {
            return Cast<T>(Component);
        }
    }
    return nullptr;
}
