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

#include "PersistencyUtilities.h"
#include "Kismet/GameplayStatics.h"

#include "Constants.h"


UPersistentSettings* PersistencyUtilities::CreateSettingsObject()
{
    UPersistentSettings* NewSettings = Cast<UPersistentSettings>(UGameplayStatics::CreateSaveGameObject(UPersistentSettings::StaticClass()));
    
    return NewSettings;
}

void PersistencyUtilities::SaveSettings(UPersistentSettings* Settings)
{
    UGameplayStatics::SaveGameToSlot(Settings, Constants::SAVE_GAME_LABEL, Constants::SAVE_GAME_INDEX);
}

UPersistentSettings* PersistencyUtilities::LoadSettings()
{
    if (UGameplayStatics::DoesSaveGameExist(Constants::SAVE_GAME_LABEL, Constants::SAVE_GAME_INDEX))
    {
        UPersistentSettings* LoadedSettings = Cast<UPersistentSettings>(UGameplayStatics::LoadGameFromSlot(Constants::SAVE_GAME_LABEL, Constants::SAVE_GAME_INDEX));
        
        return LoadedSettings;
    }
    else
    {
        return nullptr;
    }
}
