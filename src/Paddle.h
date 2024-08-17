#pragma once
#include "Core.h"

#define PADDLE_WIDTH 0.2f
#define PADDLE_HEIGHT 1.5f
#define PADDLE_EDGE_DISTANCE 0.5f
#define PADDLE_MOVE_SPEED 8.0f

#define PLAYER_CPU 0
#define PLAYER_WASD 1
#define PLAYER_ARROWS 2

typedef struct Paddle
{
    Vector2 position;
} Paddle;

void Paddle_Update(Paddle* const paddle, unsigned char playerType);
void Paddle_Draw(const Paddle* paddle, const Color color);