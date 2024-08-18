#pragma once
#include "Ball.h"
#include "Core.h"

#define PADDLE_WIDTH 0.2f
#define PADDLE_HEIGHT 1.5f
#define PADDLE_EDGE_DISTANCE 0.5f
#define PADDLE_MOVE_SPEED 8.0f
#define CPU_MAX_ERROR 1.0f

char Paddle_GetWASD();
char Paddle_GetArrows();
char Paddle_GetCPU(float paddlePosition, float ballPosition);

void Paddle_RecalcError();
void Paddle_Update(Paddle *const paddle, char movementDir);
void Paddle_Draw(const Paddle* paddle, const Color color);