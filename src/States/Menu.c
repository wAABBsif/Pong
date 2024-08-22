#include "Menu.h"
#include "Gameplay.h"

static const char* const menu_textOptions[] =
{
    "1P Game",
    "2P Game",
    "Settings",
    "Quit"
};


static float menu_textPositions[sizeof(menu_textOptions) / sizeof(char*)];

void Menu_Start(GameData* game)
{
    Gameplay_Reset(game);
    for (int i = 0; i < sizeof(menu_textOptions) / sizeof(char*); i++)
        menu_textPositions[i] = 0.5f - MeasureText(menu_textOptions[i], MENU_TEXT_SIZE * GetScreenWidth()) / (float)GetScreenWidth() / 2;
    game->menuSelection = 0;
}

void Menu_Update(GameData* game)
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        PlaySound(sounds[SOUND_MENU_MOVE]);
        game->menuSelection++;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        PlaySound(sounds[SOUND_MENU_MOVE]);
        game->menuSelection--;
    }

    if (game->menuSelection <= -1)
        game->menuSelection = 3;

    game->menuSelection %= 4;

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(sounds[SOUND_MENU_ENTER]);
        switch (game->menuSelection)
        {
            case 0:
                game->playerCount = 1;
                SwitchState(game, GAMESTATE_GAMEPLAY);
                break;
            case 1:
                game->playerCount = 2;
                SwitchState(game, GAMESTATE_GAMEPLAY);
                break;
            case 2:
                SwitchState(game, GAMESTATE_SETTINGS);
                break;
            default:
                CloseAudioDevice();
                CloseWindow();
                break;
        }
    }
}

void Menu_Draw(const GameData* game)
{
    for (int i = 0; i < sizeof(menu_textOptions) / sizeof(char*); i++)
        DrawText(menu_textOptions[i], menu_textPositions[i] * GetScreenWidth(), (MENU_TEXT_START_POSITION + i * MENU_TEXT_SPACING) * GetScreenHeight(), MENU_TEXT_SIZE * GetScreenWidth(), i == game->menuSelection ? YELLOW : RAYWHITE);
}