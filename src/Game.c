#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Core.h"
#include "SaveData.h"

#include "Objects/Paddle.h"
#include "Objects/Ball.h"

#include "States/Menu.h"
#include "States/Gameplay.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}

GameData* game;

void SetupGameStates();

void Game()
{
    SetRandomSeed(time(NULL));
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_WIDTH / DEFAULT_ASPECT_RATIO, "Pong");

    game = malloc(sizeof(GameData));

    game->paddles[0] = (Paddle){PADDLE_EDGE_DISTANCE - SCREEN_WIDTH_IN_UNITS / 2, 0};
    game->paddles[1] = (Paddle){SCREEN_WIDTH_IN_UNITS / 2 - PADDLE_EDGE_DISTANCE, 0};
    game->ball = (Ball){0, 0, BALL_DEFAULT_SPEED, GetRandomFloat(-BALL_DEFAULT_SPEED, BALL_DEFAULT_SPEED)};
    game->scores[0] = 0;
    game->scores[1] = 0;

    game->saveData.paddleColors[0] = 1;
    game->saveData.paddleColors[1] = 7;
    game->saveData.ballColor = 0;
    game->saveData.miscColor = 0;
    game->saveData.maxScore = 8;

    LoadPlayerData(&game->saveData);
    SetupGameStates();
    SwitchState(game, GAMESTATE_MENU);

    while (!WindowShouldClose())
    {
        game->gameStates[game->gameState].Update(game);
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        game->gameStates[game->gameState].Draw(game);
        EndDrawing();
    }

    free(game);

    CloseWindow();
}

void SetupGameStates()
{
    game->gameStates[GAMESTATE_MENU].Start = Menu_Start;
    game->gameStates[GAMESTATE_MENU].Update = Menu_Update;
    game->gameStates[GAMESTATE_MENU].Draw = Menu_Draw;

    // game->gameStates[GAMESTATE_SETTINGS].Update =
    // game->gameStates[GAMESTATE_SETTINGS].Draw =

    game->gameStates[GAMESTATE_GAMEPLAY].Start = Gameplay_Update;
    game->gameStates[GAMESTATE_GAMEPLAY].Update = Gameplay_Update;
    game->gameStates[GAMESTATE_GAMEPLAY].Draw = Gameplay_Draw;

    // game->gameStates[GAMESTATE_END].Update =
    // game->gameStates[GAMESTATE_END].Draw =
}