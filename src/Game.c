#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Core.h"
#include "Paddle.h"
#include "Ball.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}
#define TEXT_Y_POS 0.5f
#define TEXT_SIZE 1.0f

#define GAMEMODE_1_PLAYER 0
#define GAMEMODE_2_PLAYER 1

#define GAMESTATE_MENU 0
#define GAMESTATE_SETTINGS 1
#define GAMESTATE_GAME 2
#define GAMESTATE_END 3

typedef struct GameData
{
    Paddle paddles[2];
    Ball ball;
    int scores[2];
    char gameMode;
    SaveData saveData;
    char scoreTextOne[3];
    char scoreTextTwo[3];
} GameData;

GameData* game;

static void Update();
static void Draw();

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
    game->gameMode = 0;

    game->saveData.paddleColors[0] = 1;
    game->saveData.paddleColors[1] = 7;
    game->saveData.ballColor = 0;
    game->saveData.miscColor = 0;
    game->saveData.maxScore = 8;
    while (!WindowShouldClose())
    {
        Update();
        BeginDrawing();
        Draw();
        EndDrawing();
    }

    free(game);

    CloseWindow();
}

static void Update()
{
    Paddle_Update(&game->paddles[0], Paddle_GetWASD());
    float player2Movement = game->gameMode == GAMEMODE_1_PLAYER ? Paddle_GetCPU(game->paddles[1].position.y, Ball_PredictPositionY(&game->ball, game->paddles[1].position.x)) : Paddle_GetArrows();
    Paddle_Update(&game->paddles[1], player2Movement);
    switch (Ball_Update(&game->ball))
    {
        case BALL_PADDLE_ONE_SCORE:
            game->scores[0]++;
            break;
        case BALL_PADDLE_TWO_SCORE:
            game->scores[1]++;
            break;
        default:
            break;
    }
    ScoreToString(game->scores[0], game->scoreTextOne);
    ScoreToString(game->scores[1], game->scoreTextTwo);
    if (game->ball.velocity.x < 0)
        Ball_ApplyCollision(&game->ball, &game->paddles[0]);
    if (&game->paddles[1] && game->ball.velocity.x > 0)
        Ball_ApplyCollision(&game->ball, &game->paddles[1]);
}

static void Draw()
{
    ClearBackground(BACKGROUND_COLOR);
    Paddle_Draw(&game->paddles[0], availableColors[game->saveData.paddleColors[0]]);
    Paddle_Draw(&game->paddles[1], availableColors[game->saveData.paddleColors[1]]);
    Ball_Draw(&game->ball, availableColors[game->saveData.ballColor]);
    DrawRectangle(0, 0, GetScreenWidth(), UNIT_TO_PIXELS * BORDER_SIZE, availableColors[game->saveData.miscColor]);
    DrawRectangle(0, GetScreenHeight() - UNIT_TO_PIXELS * BORDER_SIZE, GetScreenWidth(), UNIT_TO_PIXELS * BORDER_SIZE, availableColors[game->saveData.miscColor]);
    DrawText(game->scoreTextOne, (GetScreenWidth() >> 2) - (MeasureText(game->scoreTextOne, TEXT_SIZE * UNIT_TO_PIXELS) >> 1), TEXT_Y_POS * UNIT_TO_PIXELS, TEXT_SIZE * UNIT_TO_PIXELS, availableColors[game->saveData.miscColor]);
    DrawText(game->scoreTextTwo, (GetScreenWidth() >> 2) * 3 - (MeasureText(game->scoreTextTwo, TEXT_SIZE * UNIT_TO_PIXELS) >> 1), TEXT_Y_POS * UNIT_TO_PIXELS, TEXT_SIZE * UNIT_TO_PIXELS, availableColors[game->saveData.miscColor]);
}