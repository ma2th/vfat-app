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

#include "VFATPawn.h"

#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Engine/StaticMesh.h"

#include "VFATGameMode.h"
#include "Utilities/Constants.h"
#include "Utilities/MathUtilities.h"
#include "Utilities/WorldUtilities.h"

// https://github.com/ma2th/btc
// #include "BTC.h"


AVFATPawn::AVFATPawn()
{
    PrimaryActorTick.bCanEverTick = false;
    
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    AutoReceiveInput = EAutoReceiveInput::Player0;
    
    ConstructionTimeSetup();
}

void AVFATPawn::ConstructionTimeSetup()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    
    VRCameraScene = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraScene"));
    VRCameraScene->SetupAttachment(RootComponent);
    
    VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
    VRCamera->SetupAttachment(VRCameraScene);
}

void AVFATPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAction(FName(*Constants::BUTTON_PRESSED_LABEL), IE_Pressed, this, &AVFATPawn::ButtonPressed);
}

void AVFATPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AVFATPawn::BeginPlay()
{
    Super::BeginPlay();
    
    // https://github.com/ma2th/btc
    // IBTCDeviceModule::Get().Deactivate();
    
    WorldUtilities::SetupGoogleVRRuntime(GetWorld(), VRCamera);
    RuntimeSetup();
    
    ProgramRunning = false;
    
    EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AVFATPawn::RuntimeSetup()
{
    AVFATGameMode* GameMode = Cast<AVFATGameMode>(GetWorld()->GetAuthGameMode());
    
    FixationComponent1 = CreateInteractionComponent(GameMode->FixationMesh, GameMode->SingleEyeMaterial);
    FixationComponent2 = CreateInteractionComponent(GameMode->FixationMesh, GameMode->SingleEyeMaterial);
    FixationComponent3 = CreateInteractionComponent(GameMode->FixationMesh, GameMode->SingleEyeMaterial);
    FixationComponent4 = CreateInteractionComponent(GameMode->FixationMesh, GameMode->SingleEyeMaterial);
    MovingComponent = CreateInteractionComponent(GameMode->MovingMesh, GameMode->SingleEyeMaterial);
}

USingleEyeComponent* AVFATPawn::CreateInteractionComponent(UStaticMesh* Mesh, UMaterialInterface* Material)
{
    USingleEyeComponent* Component = NewObject<USingleEyeComponent>(this, USingleEyeComponent::StaticClass());
    Component->RegisterComponent();
    Component->AttachToComponent(VRCamera, FAttachmentTransformRules::KeepRelativeTransform);
    Component->SetupMaterial(Material);
    Component->SetStaticMesh(Mesh);
    Component->SetVisibility(false);
    
    return Component;
}

void AVFATPawn::StartProgram(FEquidistantProgram Program)
{
    if (!ProgramRunning)
    {
        PrepareProgramStart(Program, false);
        Tester->SetProgram(Program);
        
        // https://github.com/ma2th/btc
        // IBTCDeviceModule::Get().Activate();
    }
}

void AVFATPawn::StartProgram(FOctopusG1Program Program)
{
    if (!ProgramRunning)
    {
        PrepareProgramStart(Program, false);
        Tester->SetProgram(Program);
        
        // https://github.com/ma2th/btc
        // IBTCDeviceModule::Get().Activate();
    }
}

void AVFATPawn::StartProgram(FTrainingProgram Program)
{
    if (!ProgramRunning)
    {
        PrepareProgramStart(Program, Program.Random_Training_Color);
        Tester->SetProgram(Program);
        
        // https://github.com/ma2th/btc
        // IBTCDeviceModule::Get().Activate();
    }
}

void AVFATPawn::PrepareProgramStart(FAbstractProgram Program, bool RandomColor)
{
    ProgramRunning = true;

    FixationComponent1->ActivateProgramMode(Program, true, false);
    WorldUtilities::MoveComponent(FixationComponent1, Constants::FIXATION_POSITION_1[0], Constants::FIXATION_POSITION_1[1], Constants::MESH_RADIUS);
    
    FixationComponent2->ActivateProgramMode(Program, true, false);
    WorldUtilities::MoveComponent(FixationComponent2, Constants::FIXATION_POSITION_2[0], Constants::FIXATION_POSITION_2[1], Constants::MESH_RADIUS);
    
    FixationComponent3->ActivateProgramMode(Program, true, false);
    WorldUtilities::MoveComponent(FixationComponent3, Constants::FIXATION_POSITION_3[0], Constants::FIXATION_POSITION_3[1], Constants::MESH_RADIUS);
    
    FixationComponent4->ActivateProgramMode(Program, true, false);
    WorldUtilities::MoveComponent(FixationComponent4, Constants::FIXATION_POSITION_4[0], Constants::FIXATION_POSITION_4[1], Constants::MESH_RADIUS);
    
    MovingComponent->ActivateProgramMode(Program, false, RandomColor);
    WorldUtilities::MoveComponent(MovingComponent, 0.0f, 0.0f, Constants::MESH_RADIUS);
    
    Tester = NewObject<UProgramTester>(this);
    Tester->ProgramDoneCallback.BindUObject(this, &AVFATPawn::ProgramDone);
    Tester->Init(MovingComponent, GetWorld());
}

void AVFATPawn::ButtonPressed()
{
    if (ProgramRunning)
    {
        Tester->ButtonPressed();
    }
}

void AVFATPawn::ProgramDone()
{
    ProgramRunning = false;
    
    // https://github.com/ma2th/btc
    // IBTCDeviceModule::Get().Deactivate();
    
    FixationComponent1->SetVisibility(false);
    FixationComponent2->SetVisibility(false);
    FixationComponent3->SetVisibility(false);
    FixationComponent4->SetVisibility(false);
    
    MovingComponent->SetVisibility(false);
    
    AVFATGameMode* GameMode = Cast<AVFATGameMode>(GetWorld()->GetAuthGameMode());
    GameMode->TestResult(Tester);
}

USingleEyeComponent* AVFATPawn::GetMovingComponent()
{
    return MovingComponent;
}

USingleEyeComponent* AVFATPawn::GetFixationComponent1()
{
    return FixationComponent1;
}


