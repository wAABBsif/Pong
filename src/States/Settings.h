#pragma once
#include "../Core.h"

#define SETTINGS_MIN_WIN_SCORE 2
#define SETTINGS_MAX_WIN_SCORE 15

#define SETTINGS_TEXT_MARGIN 0.05f
#define SETTINGS_TEXT_SIZE 0.05f
#define SETTINGS_TEXT_START_POSITION (1.5f / 14.0f)
#define SETTINGS_TEXT_SPACING (1.0f / 7.0f)

void Settings_Start(GameData* game);
void Settings_Update(GameData* game);
void Settings_Draw(const GameData* game);