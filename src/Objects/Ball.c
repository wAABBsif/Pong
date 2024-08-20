#include "Ball.h"
#include "Paddle.h"
#include "raymath.h"

char Ball_Update(Ball *const ball)
{
    if (fabsf(ball->velocity.x) > BALL_MAX_SPEED)
        ball->velocity.x = BALL_MAX_SPEED * Sign(ball->velocity.x);

    if (ball->position.y + BALL_RADIUS > SCREEN_HEIGHT_IN_UNITS / 2.0f - BORDER_SIZE)
    {
        ball->position.y = SCREEN_HEIGHT_IN_UNITS / 2.0f - BORDER_SIZE - BALL_RADIUS;
        ball->velocity.y = -ball->velocity.y;
    }

    if (ball->position.y - BALL_RADIUS < BORDER_SIZE - SCREEN_HEIGHT_IN_UNITS / 2.0f)
    {
        ball->position.y = BORDER_SIZE + BALL_RADIUS - SCREEN_HEIGHT_IN_UNITS / 2.0f;
        ball->velocity.y = -ball->velocity.y;
    }

    ball->position.x += ball->velocity.x * GetFrameTime();
    ball->position.y += ball->velocity.y * GetFrameTime();

    if (ball->position.x > SCREEN_WIDTH_IN_UNITS / 2.0f + BALL_RADIUS)
    {
        ball->position.x = -(SCREEN_WIDTH_IN_UNITS / 2.0f + BALL_RADIUS);
        ball->velocity = Vector2Scale(ball->velocity, BALL_DEFAULT_SPEED / (ball->velocity.x));
        return BALL_PADDLE_ONE_SCORE;
    }

    if (ball->position.x < -(SCREEN_WIDTH_IN_UNITS / 2.0f + BALL_RADIUS))
    {
        ball->position.x = SCREEN_WIDTH_IN_UNITS / 2.0f + BALL_RADIUS;
        ball->velocity = Vector2Scale(ball->velocity, BALL_DEFAULT_SPEED / -ball->velocity.x);
        return BALL_PADDLE_TWO_SCORE;
    }

    return BALL_NO_SCORE;
}

void Ball_ApplyCollision(Ball *const ball, const Paddle *paddle)
{
    const Rectangle ballRect = (Rectangle)
    {
        ball->position.x - BALL_RADIUS, ball->position.y - BALL_RADIUS, BALL_RADIUS * 2, BALL_RADIUS * 2
    };
    const Rectangle paddleRect = (Rectangle)
    {
        paddle->position.x - PADDLE_WIDTH / 2.0f, paddle->position.y - PADDLE_HEIGHT / 2.0f, PADDLE_WIDTH,
        PADDLE_HEIGHT
    };

    if (!CheckCollisionRecs(ballRect, paddleRect))
        return;

    if (ballRect.x + ballRect.width - ball->velocity.x * GetFrameTime() < paddleRect.x && ball->velocity.x > 0)
    {
        ball->position.x = paddle->position.x - PADDLE_WIDTH;
    }
    else if (ballRect.x - ball->velocity.x * GetFrameTime() > paddleRect.x + paddleRect.width && ball->velocity.x < 0)
    {
        ball->position.x = paddle->position.x + PADDLE_WIDTH;
    }
    else
    {
        if (ball->position.y > paddle->position.y)
            ball->position.y = paddle->position.y + PADDLE_HEIGHT + BALL_RADIUS;
        else
            ball->position.y = paddle->position.y - PADDLE_HEIGHT - BALL_RADIUS;
    }

    ball->velocity.x += BALL_SPEED_INCREASE * Sign(ball->velocity.x);

    const float offset = ball->position.y - paddle->position.y;
    Vector2 normalizedVelocity = Vector2Normalize(ball->velocity);
    normalizedVelocity.y = normalizedVelocity.y * BALL_ANGLE_KEEP + BALL_ANGLE_CHANGE * Sign(offset) * fminf(
                               fabsf(offset / (PADDLE_HEIGHT / 2.0f)), 1);
    normalizedVelocity.y = Clamp(normalizedVelocity.y, -sinf(BALL_MAX_ANGLE), sinf(BALL_MAX_ANGLE));
    normalizedVelocity.x = sqrtf(1 - normalizedVelocity.y * normalizedVelocity.y) * Sign(-ball->velocity.x);
    ball->velocity = Vector2Scale(normalizedVelocity, fabsf(ball->velocity.x / normalizedVelocity.x));
    Paddle_RecalcError(ball);
}

void Ball_Draw(const Ball *ball, const Color color)
{
    DrawCircle((ball->position.x + SCREEN_WIDTH_IN_UNITS / 2.0f) * UNITS_TO_PIXELS,
               (ball->position.y + SCREEN_HEIGHT_IN_UNITS / 2.0f) * UNITS_TO_PIXELS, BALL_RADIUS * UNITS_TO_PIXELS,
               color);
}

float Ball_PredictPositionY(const Ball* ball, float positionX)
{
    return ball->position.y + ball->velocity.y / ball->velocity.x * (positionX - ball->position.x);
}
