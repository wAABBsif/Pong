#pragma once
#include "../Core.h"

#define MENU_TEXT_SIZE 0.05f
#define MENU_TEXT_START_POSITION 0.4f
#define MENU_TEXT_SPACING 0.15f

void Menu_Start(GameData* game);
void Menu_Update(GameData* game);
void Menu_Draw(const GameData* game);