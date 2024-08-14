#include "Paddle.h"
#include "raymath.h"

void Paddle_Update(Paddle *const paddle, unsigned char playerType)
{
    bool isMovingUp = false;
    bool isMovingDown = false;

    if (playerType == PLAYER_WASD)
    {
        isMovingUp = IsKeyDown(KEY_W);
        isMovingDown = IsKeyDown(KEY_S);
    }

    if (playerType == PLAYER_ARROWS)
    {
        isMovingUp = IsKeyDown(KEY_UP);
        isMovingDown = IsKeyDown(KEY_DOWN);
    }

    if (playerType == PLAYER_CPU)
    {
        isMovingUp = true;
    }

    if (isMovingUp)
    {
        paddle->position.y -= paddle->movementSpeed * GetFrameTime();
    }

    if (isMovingDown)
    {
        paddle->position.y += paddle->movementSpeed * GetFrameTime();
    }

    paddle->position.y = Clamp(paddle->position.y, SCREEN_HEIGHT_IN_UNITS / -2.0f, SCREEN_HEIGHT_IN_UNITS / 2.0f);
}

void Paddle_Draw(const Paddle *const paddle, Color color)
{
    DrawRectangle((paddle->position.x - (PADDLE_WIDTH - SCREEN_WIDTH_IN_UNITS) / 2.0f) * UNIT_TO_PIXELS,
                  (paddle->position.y - (paddle->height - SCREEN_HEIGHT_IN_UNITS) / 2.0f) * UNIT_TO_PIXELS,
                  PADDLE_WIDTH * UNIT_TO_PIXELS, paddle->height * UNIT_TO_PIXELS, color);
}
