#include <math.h>
#include <stdlib.h>
#include "Core.h"
#include "Paddle.h"
#include "Ball.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}

typedef struct GameData
{
    Paddle paddles[2];
    Ball ball;
    SaveData saveData;
} GameData;

GameData* game;

static void Update();
static void Draw();

void Game()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_WIDTH / DEFAULT_ASPECT_RATIO, "Pong");

    game = malloc(sizeof(GameData));

    game->paddles[0] = (Paddle){DEFAULT_EDGE_DISTANCE - SCREEN_WIDTH_IN_UNITS / 2, 0, DEFAULT_PADDLE_HEIGHT, DEFAULT_MOVE_SPEED};
    game->paddles[1] = (Paddle){SCREEN_WIDTH_IN_UNITS / 2 - DEFAULT_EDGE_DISTANCE, 0, DEFAULT_PADDLE_HEIGHT, DEFAULT_MOVE_SPEED};
    game->ball = (Ball){0, 0, BALL_DEFAULT_SPEED, GetRandomValue(-BALL_DEFAULT_SPEED, BALL_DEFAULT_SPEED), BALL_DEFAULT_RADIUS};

    game->saveData.paddleColors[0] = 1;
    game->saveData.paddleColors[1] = 7;
    game->saveData.ballColor = 0;
    game->saveData.miscColor = 0;
    game->saveData.highScore = 100;

    while (!WindowShouldClose())
    {
        Update();
        BeginDrawing();
        Draw();
        EndDrawing();
    }

    CloseWindow();
}

static void Update()
{
    Paddle_Update(&game->paddles[0], PLAYER_WASD);
    if (&game->paddles[1])
        Paddle_Update(&game->paddles[1], PLAYER_ARROWS);
    Ball_Update(&game->ball);
    if (game->ball.velocity.x < 0)
        Ball_ApplyCollision(&game->ball, &game->paddles[0]);
    if (&game->paddles[1] && game->ball.velocity.x > 0)
        Ball_ApplyCollision(&game->ball, &game->paddles[1]);
}

static void Draw()
{
    ClearBackground(BACKGROUND_COLOR);
    Paddle_Draw(&game->paddles[0], availableColors[game->saveData.paddleColors[0]]);
    if (&game->paddles[1])
        Paddle_Draw(&game->paddles[1], availableColors[game->saveData.paddleColors[1]]);
    Ball_Draw(&game->ball, availableColors[game->saveData.ballColor]);
    DrawRectangle(0, 0, GetScreenWidth(), UNIT_TO_PIXELS * BORDER_SIZE, availableColors[game->saveData.miscColor]);
    DrawRectangle(0, GetScreenHeight() - UNIT_TO_PIXELS * BORDER_SIZE, GetScreenWidth(), UNIT_TO_PIXELS * BORDER_SIZE, availableColors[game->saveData.miscColor]);;
}