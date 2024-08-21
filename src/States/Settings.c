#include "Settings.h"
#include "../SaveData.h"
#include "raymath.h"

static const char* const settings_textOptions[] =
{
    "Left Paddle Color",
    "Right Paddle Color",
    "Ball Color",
    "Misc. Color",
    "Score Needed To Win: %02i",
    "Back"
};

void Settings_Start(GameData* game)
{
    game->menuSelection = 0;
}

void Settings_Update(GameData* game)
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        game->menuSelection++;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        game->menuSelection--;

    if (game->menuSelection <= -1)
        game->menuSelection = 5;

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        ((char*)&game->saveData)[game->menuSelection]++;

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        ((char*)&game->saveData)[game->menuSelection]--;

    if (game->menuSelection <= 3)
        ((char*)&game->saveData)[game->menuSelection] %= sizeof(availableColors) / sizeof(Color);

    game->saveData.maxScore = Clamp(game->saveData.maxScore, SETTINGS_MIN_WIN_SCORE, SETTINGS_MAX_WIN_SCORE);

    if (IsKeyPressed(KEY_ENTER) && game->menuSelection == 5)
    {
        SavePlayerData(game->saveData);
        SwitchState(game, GAMESTATE_MENU);
    }

    game->menuSelection %= 6;
}

void Settings_Draw(const GameData* game)
{
    for (int i = 0; i < 4; i++)
    {
        Color c = availableColors[((char*)&game->saveData)[i]];
        if (i != game->menuSelection)
            c = (Color){c.r / 2, c.g / 2, c.b / 2, c.a};
        DrawText(settings_textOptions[i], SETTINGS_TEXT_MARGIN * GetScreenWidth(), (SETTINGS_TEXT_START_POSITION + i * SETTINGS_TEXT_SPACING) * GetScreenHeight(), SETTINGS_TEXT_SIZE * GetScreenWidth(), c);
    }

    for (int i = 4; i < 6; i++)
        DrawText(TextFormat(settings_textOptions[i], game->saveData.maxScore), SETTINGS_TEXT_MARGIN * GetScreenWidth(), (SETTINGS_TEXT_START_POSITION + i * SETTINGS_TEXT_SPACING) * GetScreenHeight(), SETTINGS_TEXT_SIZE * GetScreenWidth(), i == game->menuSelection ? YELLOW : RAYWHITE);
}