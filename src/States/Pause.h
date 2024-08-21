#pragma once
#include "../Core.h"

#define PAUSE_TEXT_SIZE 0.05f
#define PAUSE_TEXT_START_POSITION 0.425f
#define PAUSE_TEXT_SPACING 0.15f

void Pause_Start(GameData* game);
void Pause_Update(GameData* game);
void Pause_Draw(const GameData* game);