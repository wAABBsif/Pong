#include "Menu.h"

#include "Gameplay.h"

unsigned char menuSelection = 0;
const char* const menuOptions[] =
{
    "1P Game",
    "2P Game",
    "Settings",
    "Quit"
};

float menuPositions[sizeof(menuOptions) / sizeof(char*)];

void Menu_Start(GameData* game)
{
    for (int i = 0; i < sizeof(menuOptions) / sizeof(char*); i++)
        menuPositions[i] = 0.5f - MeasureText(menuOptions[i], MENU_TEXT_SIZE * GetScreenWidth()) / (float)GetScreenWidth() / 2;
    menuSelection = 0;
}

void Menu_Update(GameData* game)
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        menuSelection++;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        menuSelection--;
    menuSelection %= 4;

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (menuSelection)
        {
            case 0:
                playerCount = 1;
                SwitchState(game, GAMESTATE_GAMEPLAY);
                break;
            case 1:
                playerCount = 2;
                SwitchState(game, GAMESTATE_GAMEPLAY);
                break;
            case 2:
                SwitchState(game, GAMESTATE_SETTINGS);
                break;
            case 3:
                CloseWindow();
                break;
        }
    }
}

void Menu_Draw(const GameData* game)
{
    for (int i = 0; i < sizeof(menuOptions) / sizeof(char*); i++)
    {
        DrawText(menuOptions[i], menuPositions[i] * GetScreenWidth(), (MENU_TEXT_START_POSITION + i * MENU_TEXT_SPACING) * GetScreenHeight(), MENU_TEXT_SIZE * GetScreenWidth(), i == menuSelection ? YELLOW : RAYWHITE);
    }
}