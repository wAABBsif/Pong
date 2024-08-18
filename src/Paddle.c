#include "Paddle.h"
#include "Ball.h"
#include "raymath.h"

static float cpuError = 0;

char Paddle_GetWASD()
{
    if (IsKeyDown(KEY_S))
        return 1;

    if (IsKeyDown(KEY_W))
        return -1;

    return 0;
}

char Paddle_GetArrows()
{
    if (IsKeyDown(KEY_DOWN))
        return 1;

    if (IsKeyDown(KEY_UP))
        return -1;

    return 0;
}

char Paddle_GetCPU(float paddlePosition, float ballPosition)
{
    ballPosition += cpuError;

    if (fabsf(paddlePosition - ballPosition) < PADDLE_HEIGHT / 2)
        return 0;

    if (paddlePosition < ballPosition)
        return 1;

    return -1;
}

void Paddle_RecalcError()
{
    cpuError = GetRandomFloat(-CPU_MAX_ERROR, CPU_MAX_ERROR);
}

void Paddle_Update(Paddle *const paddle, char movementDir)
{
    if (movementDir == 1)
        paddle->position.y += PADDLE_MOVE_SPEED * GetFrameTime();

    if (movementDir == -1)
        paddle->position.y -= PADDLE_MOVE_SPEED * GetFrameTime();

    paddle->position.y = Clamp(paddle->position.y, (SCREEN_HEIGHT_IN_UNITS - PADDLE_HEIGHT - BORDER_SIZE) / -2.0f, (SCREEN_HEIGHT_IN_UNITS - PADDLE_HEIGHT - BORDER_SIZE) / 2.0f);
}

void Paddle_Draw(const Paddle *const paddle, const Color color)
{
    DrawRectangle((paddle->position.x - (PADDLE_WIDTH - SCREEN_WIDTH_IN_UNITS) / 2.0f) * UNIT_TO_PIXELS,
                  (paddle->position.y - (PADDLE_HEIGHT - SCREEN_HEIGHT_IN_UNITS) / 2.0f) * UNIT_TO_PIXELS,
                  PADDLE_WIDTH * UNIT_TO_PIXELS, PADDLE_HEIGHT * UNIT_TO_PIXELS, color);
}
