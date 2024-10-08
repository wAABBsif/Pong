#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Core.h"
#include "SaveData.h"

#include "Objects/Paddle.h"
#include "Objects/Ball.h"

#include "States/Menu.h"
#include "States/Settings.h"
#include "States/Gameplay.h"
#include "States/Pause.h"
#include "States/End.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}

GameData* game;
Sound sounds[SOUND_COUNT];

void InitializeGameStates();
void InitializeSounds();

void Game()
{
    SetRandomSeed(time(NULL));
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_WIDTH / DEFAULT_ASPECT_RATIO, "Pong");
    InitAudioDevice();

    game = malloc(sizeof(GameData));

    game->playerCount = 1;
    game->menuSelection = 0;

    game->saveData.paddleColors[0] = 1;
    game->saveData.paddleColors[1] = 7;
    game->saveData.ballColor = 0;
    game->saveData.miscColor = 0;
    game->saveData.volume = 10;
    game->saveData.maxScore = 5;

    LoadPlayerData(&game->saveData);
    InitializeGameStates();
    InitializeSounds();
    SwitchState(game, GAMESTATE_MENU);
    SetMasterVolume(game->saveData.volume / 10.0f);

    while (!WindowShouldClose())
    {
        game->gameStates[game->gameState].Update(game);
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        game->gameStates[game->gameState].Draw(game);
        if (IsKeyDown(KEY_F))
            DrawFPS(4,4);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}

void InitializeGameStates()
{
    game->gameStates[GAMESTATE_MENU].Start = Menu_Start;
    game->gameStates[GAMESTATE_MENU].Update = Menu_Update;
    game->gameStates[GAMESTATE_MENU].Draw = Menu_Draw;

    game->gameStates[GAMESTATE_SETTINGS].Start = Settings_Start;
    game->gameStates[GAMESTATE_SETTINGS].Update = Settings_Update;
    game->gameStates[GAMESTATE_SETTINGS].Draw = Settings_Draw;

    game->gameStates[GAMESTATE_GAMEPLAY].Start = Gameplay_Update;
    game->gameStates[GAMESTATE_GAMEPLAY].Update = Gameplay_Update;
    game->gameStates[GAMESTATE_GAMEPLAY].Draw = Gameplay_Draw;

    game->gameStates[GAMESTATE_PAUSE].Start = Pause_Start;
    game->gameStates[GAMESTATE_PAUSE].Update = Pause_Update;
    game->gameStates[GAMESTATE_PAUSE].Draw = Pause_Draw;

    game->gameStates[GAMESTATE_END].Start = End_Start;
    game->gameStates[GAMESTATE_END].Update = End_Update;
    game->gameStates[GAMESTATE_END].Draw = End_Draw;
}

void InitializeSounds()
{
    sounds[SOUND_MENU_MOVE] = LoadSound("res/menuMove.wav");
    sounds[SOUND_MENU_ENTER] = LoadSound("res/menuEnter.wav");
    sounds[SOUND_BALL_BOUNCE] = LoadSound("res/ballBounce.wav");
    sounds[SOUND_POINT_SCORED] = LoadSound("res/pointScored.wav");
    sounds[SOUND_GAME_END] = LoadSound("res/gameEnd.wav");
}