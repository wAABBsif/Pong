#include "Gameplay.h"
#include "../Objects/Ball.h"
#include "../Objects/Paddle.h"

void Gameplay_Start(GameData* game)
{
    return;
}

void Gameplay_Update(GameData* game)
{
    if (IsKeyDown(KEY_P) || IsKeyDown(KEY_PAUSE))
    {
        SwitchState(game, GAMESTATE_PAUSE);
        return;
    }

    Paddle_Update(&game->paddles[0], Paddle_GetWASD());
    const float player2Movement = game->playerCount == 1 ? Paddle_GetCPU(game->paddles[1].position.y, Ball_PredictPositionY(&game->ball, game->paddles[1].position.x)) : Paddle_GetArrows();
    Paddle_Update(&game->paddles[1], player2Movement);

    switch (Ball_Update(&game->ball))
    {
        case BALL_PADDLE_ONE_SCORE:
            game->scores[0]++;
            if (game->scores[0] >= game->saveData.maxScore)
            {
                SwitchState(game,GAMESTATE_END);
                return;
            }
            break;
        case BALL_PADDLE_TWO_SCORE:
            game->scores[1]++;
            if (game->scores[1] >= game->saveData.maxScore)
            {
                SwitchState(game,GAMESTATE_END);
                return;
            }
            break;
        default:
            break;
    }

    ScoreToString(game->scores[0], game->scoreTextOne);
    ScoreToString(game->scores[1], game->scoreTextTwo);

    if (game->ball.velocity.x < 0)
        Ball_ApplyCollision(&game->ball, &game->paddles[0]);
    if (game->ball.velocity.x > 0)
        Ball_ApplyCollision(&game->ball, &game->paddles[1]);
}

void Gameplay_Draw(const GameData* game)
{
    Paddle_Draw(&game->paddles[0], availableColors[game->saveData.paddleColors[0]]);
    Paddle_Draw(&game->paddles[1], availableColors[game->saveData.paddleColors[1]]);
    Ball_Draw(&game->ball, availableColors[game->saveData.ballColor]);

    DrawRectangle(0, 0, GetScreenWidth(), UNITS_TO_PIXELS * BORDER_SIZE, availableColors[game->saveData.miscColor]);
    DrawRectangle(0, GetScreenHeight() - UNITS_TO_PIXELS * BORDER_SIZE, GetScreenWidth(), UNITS_TO_PIXELS * BORDER_SIZE, availableColors[game->saveData.miscColor]);

    DrawText(game->scoreTextOne, (GetScreenWidth() >> 2) - (MeasureText(game->scoreTextOne, SCORE_TEXT_SIZE * UNITS_TO_PIXELS) >> 1), SCORE_TEXT_Y_POS * UNITS_TO_PIXELS, SCORE_TEXT_SIZE * UNITS_TO_PIXELS, availableColors[game->saveData.miscColor]);
    DrawText(game->scoreTextTwo, (GetScreenWidth() >> 2) * 3 - (MeasureText(game->scoreTextTwo, SCORE_TEXT_SIZE * UNITS_TO_PIXELS) >> 1), SCORE_TEXT_Y_POS * UNITS_TO_PIXELS, SCORE_TEXT_SIZE * UNITS_TO_PIXELS, availableColors[game->saveData.miscColor]);
}

void Gameplay_Reset(GameData* game)
{
    game->paddles[0] = (Paddle){PADDLE_EDGE_DISTANCE - SCREEN_WIDTH_IN_UNITS / 2, 0};
    game->paddles[1] = (Paddle){SCREEN_WIDTH_IN_UNITS / 2 - PADDLE_EDGE_DISTANCE, 0};
    game->ball = (Ball){0, 0, BALL_DEFAULT_SPEED, GetRandomFloat(-BALL_DEFAULT_SPEED, BALL_DEFAULT_SPEED)};

    game->scores[0] = 0;
    game->scores[1] = 0;
}