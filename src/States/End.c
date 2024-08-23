#include "End.h"
#include "Gameplay.h"

static const char* const end_textLines[] =
{
    "Player 1 has won!",
    "Player 2 has won!",
    "CPU has won!"
};

static float end_textPositions[sizeof(end_textLines) / sizeof(char*)];
static float end_timer;

void End_Start(GameData* game)
{
    PlaySound(sounds[SOUND_GAME_END]);
    for (int i = 0; i < sizeof(end_textLines) / sizeof(char*); i++)
        end_textPositions[i] = 0.5f - MeasureText(end_textLines[i], END_TEXT_SIZE * GetScreenWidth()) / (float)GetScreenWidth() / 2;
    end_timer = END_WAIT_TIME;
}

void End_Update(GameData* game)
{
    end_timer -= GetFrameTime();
    if (end_timer <= 0)
        SwitchState(game, GAMESTATE_MENU);
}

void End_Draw(const GameData* game)
{
    const char index = game->scores[0] > game->scores[1] ? 0 : game->playerCount == 2 ? 1 : 2;
    DrawText(end_textLines[index], end_textPositions[index] * GetScreenWidth(), GetScreenHeight() / 2  - END_TEXT_SIZE * GetScreenHeight(), END_TEXT_SIZE * GetScreenWidth(), availableColors[game->saveData.paddleColors[game->scores[0] > game->scores[1] ? 0 : 1]]);
}