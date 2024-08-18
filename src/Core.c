#include "Core.h"

float Sign(const float n)
{
    return n >= 0 ? 1 : -1;
}

void ScoreToString(int score, char* str)
{
    if (score > 99)
    {
        str = "99";
        return;
    }

    if (score > 9)
    {
        str[0] = score / 10 + '0';
        str[1] = score % 10 + '0';
        str[2] = 0;
        return;
    }

    str[0] = score + '0';
    str[1] = 0;
}

float GetRandomFloat(const float min, const float max)
{
    return GetRandomValue(min * 1000, max * 1000) / (float)1000;
}