#include <math.h>
#include <stdlib.h>
#include "Core.h"
#include "Paddle.h"
#include "Ball.h"

#define DEFAULT_BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}
#define DEFAULT_FOREGROUND_COLOR RAYWHITE

void Update();
void Draw();

Paddle* paddleOne;
Paddle* paddleTwo;
Ball* ball;

void Game()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_WIDTH / DEFAULT_ASPECT_RATIO, "Pong");

    paddleOne = malloc(sizeof(Paddle) * 2 + sizeof(Ball));
    paddleTwo = &paddleOne[1];
    ball = (Ball*)&paddleOne[2];

    *paddleOne = (Paddle){DEFAULT_EDGE_DISTANCE - SCREEN_WIDTH_IN_UNITS / 2, 0, DEFAULT_PADDLE_HEIGHT, DEFAULT_MOVE_SPEED};
    *paddleTwo = (Paddle){SCREEN_WIDTH_IN_UNITS / 2 - DEFAULT_EDGE_DISTANCE, 0, DEFAULT_PADDLE_HEIGHT, DEFAULT_MOVE_SPEED};
    *ball = (Ball){0, 0, BALL_DEFAULT_SPEED, sinf(GetRandomValue(-BALL_MAX_ANGLE * RAD2DEG, BALL_MAX_ANGLE * RAD2DEG) * DEG2RAD) * BALL_DEFAULT_SPEED, BALL_DEFAULT_RADIUS};

    while (!WindowShouldClose())
    {
        Update();
        BeginDrawing();
        Draw();
        EndDrawing();
    }

    CloseWindow();
}

void Update()
{
    Paddle_Update(paddleOne, PLAYER_WASD);
    if (paddleTwo)
        Paddle_Update(paddleTwo, PLAYER_ARROWS);
    Ball_Update(ball);
    if (ball->velocity.x < 0)
        Ball_ApplyCollision(ball, paddleOne);
    if (paddleTwo && ball->velocity.x > 0)
        Ball_ApplyCollision(ball, paddleTwo);
}

void Draw()
{
    ClearBackground(DEFAULT_BACKGROUND_COLOR);
    Paddle_Draw(paddleOne, DEFAULT_FOREGROUND_COLOR);
    if (paddleTwo)
        Paddle_Draw(paddleTwo, DEFAULT_FOREGROUND_COLOR);
    Ball_Draw(ball, DEFAULT_FOREGROUND_COLOR);
    DrawRectangle(0, 0, GetScreenWidth(), UNIT_TO_PIXELS * BORDER_SIZE, DEFAULT_FOREGROUND_COLOR);
    DrawRectangle(0, GetScreenHeight() - UNIT_TO_PIXELS * BORDER_SIZE, GetScreenWidth(), UNIT_TO_PIXELS * BORDER_SIZE, DEFAULT_FOREGROUND_COLOR);
}