#pragma once
#include "raylib.h"

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_ASPECT_RATIO (16.0f/9.0f)
#define UNITS_TO_PIXELS (GetScreenWidth() / 16.0f)

#define SCREEN_WIDTH_IN_UNITS 16.0f
#define SCREEN_HEIGHT_IN_UNITS (SCREEN_WIDTH_IN_UNITS / ((float)GetScreenWidth() / (float)GetScreenHeight()))

#define BORDER_SIZE 0.2f

#define GAMESTATE_MENU 0
#define GAMESTATE_SETTINGS 1
#define GAMESTATE_GAMEPLAY 2
#define GAMESTATE_PAUSE 3
#define GAMESTATE_END 4
#define GAMESTATE_COUNT 5

typedef struct GameData GameData;

float Sign(float n);
float GetRandomFloat(float min, float max);
float InverseLerp(const float min, const float max, const float value);
void ScoreToString(const unsigned char score, char* str);
void SwitchState(GameData* game, char newState);

typedef struct Paddle
{
    Vector2 position;
} Paddle;

typedef struct Ball
{
    Vector2 position;
    Vector2 velocity;
} Ball;

typedef struct SaveData
{
    unsigned char paddleColors[2];
    unsigned char ballColor;
    unsigned char miscColor;
    unsigned char maxScore;
} SaveData;

typedef struct GameState
{
    void (*Start)(GameData* game);
    void (*Update)(GameData* game);
    void (*Draw)(const GameData* game);
} GameState;

const static Color availableColors[] =
{
    RAYWHITE,
    (Color){0, 115, 255, 255},
    (Color){0, 0, 160, 255},
    VIOLET,
    (Color){0, 200, 45, 255},
    YELLOW,
    ORANGE,
    (Color){255, 70, 70, 255}
};

struct GameData
{
    GameState gameStates[GAMESTATE_COUNT];
    Paddle paddles[2];
    Ball ball;
    SaveData saveData;
    char menuSelection;
    unsigned char playerCount;
    unsigned char gameState;
    unsigned char scores[2];
    char scoreTextOne[3];
    char scoreTextTwo[3];
};
