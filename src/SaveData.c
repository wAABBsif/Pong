#include "SaveData.h"

#include <stdio.h>

void SavePlayerData(SaveData saveData)
{

}

void LoadPlayerData(SaveData* saveData)
{
    FILE* stream = fopen(PLAYER_DATA_FILENAME, "r");
    if (!stream)
    {
        printf("Could not load player data!\n");
        return;
    }
    fread(saveData, sizeof(SaveData), sizeof(SaveData), stream);
}