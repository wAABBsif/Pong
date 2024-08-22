#include "Pause.h"

#include "Menu.h"

static const char* const pause_textOptions[] =
{
    "Resume",
    "Exit to Menu"
};

static float pause_textPositions[sizeof(pause_textOptions) / sizeof(char*)];

void Pause_Start(GameData* game)
{
    game->menuSelection = 0;
    for (int i = 0; i < sizeof(pause_textOptions) / sizeof(char*); i++)
        pause_textPositions[i] = 0.5f - MeasureText(pause_textOptions[i], PAUSE_TEXT_SIZE * GetScreenWidth()) / (float)GetScreenWidth() / 2;
}

void Pause_Update(GameData* game)
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
        game->menuSelection = 1;

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(sounds[SOUND_MENU_ENTER]);
        switch (game->menuSelection)
        {
            case 1:
                SwitchState(game, GAMESTATE_MENU);
                break;
            default:
                SwitchState(game, GAMESTATE_GAMEPLAY);
                break;
        }
    }

    game->menuSelection %= 2;
}

void Pause_Draw(const GameData* game)
{
    for (int i = 0; i < sizeof(pause_textOptions) / sizeof(char*); i++)
        DrawText(pause_textOptions[i], pause_textPositions[i] * GetScreenWidth(), (PAUSE_TEXT_START_POSITION + i * PAUSE_TEXT_SPACING) * GetScreenHeight(), PAUSE_TEXT_SIZE * GetScreenWidth(), i == game->menuSelection ? YELLOW : RAYWHITE);

}