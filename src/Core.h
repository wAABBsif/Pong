#pragma once
#include "raylib.h"

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_ASPECT_RATIO (16.0f/9.0f)
#define UNIT_TO_PIXELS (GetScreenWidth() / 16.0f)

#define SCREEN_WIDTH_IN_UNITS 16.0f
#define SCREEN_HEIGHT_IN_UNITS (SCREEN_WIDTH_IN_UNITS / ((float)GetScreenWidth() / (float)GetScreenHeight()))

#define BORDER_SIZE 0.2f

float Sign(float n);
void ScoreToString(int score, char* str);

typedef struct SaveData
{
    unsigned char paddleColors[2];
    unsigned char ballColor;
    unsigned char miscColor;
    unsigned char maxScore;
} SaveData;

static Color availableColors[8] =
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