#include "Ball.h"
#include <stdlib.h>
#include "raymath.h"

void Ball_Update(Ball* const ball)
{
    if (abs(ball->position.x) > SCREEN_WIDTH_IN_UNITS / 2.0f + ball->radius)
        ball->position.x = -ball->position.x;

    if (ball->position.y + ball->radius > SCREEN_HEIGHT_IN_UNITS / 2.0f - BORDER_SIZE)
    {
        ball->position.y = SCREEN_HEIGHT_IN_UNITS / 2.0f - BORDER_SIZE - ball->radius;
        ball->velocity.y = -ball->velocity.y;
    }

    if (ball->position.y - ball->radius < BORDER_SIZE - SCREEN_HEIGHT_IN_UNITS / 2.0f)
    {
        ball->position.y = BORDER_SIZE + ball->radius - SCREEN_HEIGHT_IN_UNITS / 2.0f;
        ball->velocity.y = -ball->velocity.y;
    }

    ball->position.x += ball->velocity.x * GetFrameTime();
    ball->position.y += ball->velocity.y * GetFrameTime();
}

void Ball_ApplyCollision(Ball* const ball, const Paddle* paddle)
{
    const Rectangle ballRect = (Rectangle){ball->position.x - ball->radius, ball->position.y - ball->radius, ball->radius * 2, ball->radius * 2};
    const Rectangle paddleRect = (Rectangle){paddle->position.x - PADDLE_WIDTH / 2.0f, paddle->position.y - paddle->height / 2.0f, PADDLE_WIDTH, paddle->height};

    if (CheckCollisionRecs(ballRect, paddleRect))
    {
        if (ballRect.x + ballRect.width - ball->velocity.x * GetFrameTime() < paddleRect.x && ball->velocity.x > 0)
            ball->position.x = paddle->position.x - PADDLE_WIDTH;
        else if (ballRect.x - ball->velocity.x * GetFrameTime() > paddleRect.x + paddleRect.width && ball->velocity.x < 0)
            ball->position.x = paddle->position.x + PADDLE_WIDTH;
        else
        {
            if (ball->position.y > paddle->position.y)
                ball->position.y = paddle->position.x + paddle->height + ball->radius;
            else
                ball->position.y = paddle->position.x - paddle->height - ball->radius;
        }

        float offset = ball->position.y - paddle->position.y;
        Vector2 normalizedVelocity = Vector2Normalize(ball->velocity);
        normalizedVelocity.y = normalizedVelocity.y * BALL_ANGLE_KEEP + BALL_ANGLE_CHANGE * Sign(offset) * fminf(fabsf(offset / (paddle->height / 2.0f)), 1);
        normalizedVelocity.y = Clamp(normalizedVelocity.y, -sinf(BALL_MAX_ANGLE), sinf(BALL_MAX_ANGLE));
        normalizedVelocity.x = sqrtf(1 - normalizedVelocity.y * normalizedVelocity.y) * Sign(-ball->velocity.x);
        ball->velocity = Vector2Scale(normalizedVelocity, fabsf(ball->velocity.x / normalizedVelocity.x));
    }
}

void Ball_Draw(const Ball* ball, const Color color)
{
    DrawCircle((ball->position.x + SCREEN_WIDTH_IN_UNITS / 2.0f) * UNIT_TO_PIXELS, (ball->position.y + SCREEN_HEIGHT_IN_UNITS / 2.0f) * UNIT_TO_PIXELS, ball->radius * UNIT_TO_PIXELS, color);
}