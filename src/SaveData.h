#pragma once
#include "Core.h"

#define PLAYER_DATA_FILENAME "Pong.sav"

void SavePlayerData(SaveData saveData);
void LoadPlayerData(SaveData* saveData);