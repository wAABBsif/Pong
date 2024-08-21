#include "End.h"

const char* const endGameTexts[] =
{
    "Player 1 has won!",
    "Player 2 has won!",
    "CPU has won!"
};

float endGameTextPositions[sizeof(endGameTexts) / sizeof(char*)];
static float timer;

void End_Start(GameData* game)
{
    for (int i = 0; i < sizeof(endGameTexts) / sizeof(char*); i++)
        endGameTextPositions[i] = 0.5f - MeasureText(endGameTexts[i], END_TEXT_SIZE * GetScreenWidth()) / (float)GetScreenWidth() / 2;
    timer = END_WAIT_TIME;
}

void End_Update(GameData* game)
{
    timer -= GetFrameTime();
    if (timer <= 0)
        SwitchState(game, GAMESTATE_MENU);
}

void End_Draw(const GameData* game)
{
    char index = game->scores[0] > game->scores[1] ? 0 : game->playerCount == 2 ? 1 : 2;
    DrawText(endGameTexts[index], endGameTextPositions[index] * GetScreenWidth(), GetScreenHeight() / 2, END_TEXT_SIZE * GetScreenWidth(), availableColors[game->saveData.miscColor]);
}