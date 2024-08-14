#pragma once
#include "raylib.h"

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_ASPECT_RATIO (16.0f/9.0f)
#define UNIT_TO_PIXELS (GetScreenWidth() / 16.0f)

#define SCREEN_WIDTH_IN_UNITS 16.0f
#define SCREEN_HEIGHT_IN_UNITS (SCREEN_WIDTH_IN_UNITS / ((float)GetScreenWidth() / (float)GetScreenHeight()))