#pragma once
#include "Core.h"
#include "Paddle.h"

#define BALL_DEFAULT_SPEED 5.5f
#define BALL_DEFAULT_RADIUS 0.3f
#define BALL_MAX_ANGLE 60.0f * DEG2RAD
#define BALL_ANGLE_CHANGE 0.5
#define BALL_ANGLE_KEEP 0.8

typedef struct Ball
{
    Vector2 position;
    Vector2 velocity;
    float radius;
} Ball;

void Ball_Update(Ball* const ball);
void Ball_Draw(const Ball* ball, const Color color);
void Ball_ApplyCollision(Ball* const ball, const Paddle* paddle);