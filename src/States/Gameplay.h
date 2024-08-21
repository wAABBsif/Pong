#pragma once
#include "../Core.h"

#define SCORE_TEXT_Y_POS 0.5f
#define SCORE_TEXT_SIZE 1.0f

void Gameplay_Start(GameData* game);
void Gameplay_Update(GameData* game);
void Gameplay_Draw(const GameData* game);