#include <stdlib.h>
#include "Core.h"
#include "Paddle.h"

#define DEFAULT_BACKGROUND_COLOR (Color){0x10, 0x10, 0x10, 0xFF}
#define DEFAULT_FOREGROUND_COLOR RED

void Update();
void Draw();

Paddle* playerOne;
Paddle* playerTwo;

void Game()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_WIDTH / DEFAULT_ASPECT_RATIO,"Pong");

    playerOne = malloc(sizeof(Paddle));
    playerTwo = malloc(sizeof(Paddle));

    *playerOne = (Paddle){DEFAULT_EDGE_DISTANCE - SCREEN_WIDTH_IN_UNITS / 2, 0, DEFAULT_PADDLE_HEIGHT, DEFAULT_MOVE_SPEED};
    *playerTwo = (Paddle){ SCREEN_WIDTH_IN_UNITS / 2 - DEFAULT_EDGE_DISTANCE, 0, DEFAULT_PADDLE_HEIGHT, DEFAULT_MOVE_SPEED};

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
    Paddle_Update(playerOne, PLAYER_WASD);
    if (playerTwo)
        Paddle_Update(playerTwo, PLAYER_ARROWS);
}

void Draw()
{
    ClearBackground(DEFAULT_BACKGROUND_COLOR);
    Paddle_Draw(playerOne, DEFAULT_FOREGROUND_COLOR);
    if (playerTwo)
        Paddle_Draw(playerTwo, DEFAULT_FOREGROUND_COLOR);
}