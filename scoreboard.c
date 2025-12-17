#include "scoreboard.h"
#include <stdio.h>
#include <string.h>

#define MAX_SCORES 5
#define SCORE_FILE "ranking.bin"

static TIPO_SCORE highScores[MAX_SCORES];

void LoadHighScores(void)
{
    FILE *file = fopen(SCORE_FILE, "rb");
    
    if (file == NULL)
    {
        for (int i = 0; i < MAX_SCORES; i++)
        {
            strcpy(highScores[i].nome, "NINGUEM");
            highScores[i].score = 0;
        }
        return;
    }
    
    fread(highScores, sizeof(TIPO_SCORE), MAX_SCORES, file);
    fclose(file);
}

void SaveHighScores(void)
{
    FILE *file = fopen(SCORE_FILE, "wb");
    if (file == NULL) return;
    
    fwrite(highScores, sizeof(TIPO_SCORE), MAX_SCORES, file);
    fclose(file);
}

bool IsHighScore(int score)
{
    return (score > highScores[MAX_SCORES - 1].score);
}

void AddHighScore(int score, const char *name)
{
    highScores[MAX_SCORES - 1].score = score;
    strncpy(highScores[MAX_SCORES - 1].nome, name, 19);
    highScores[MAX_SCORES - 1].nome[19] = '\0';

    for (int i = MAX_SCORES - 1; i > 0; i--)
    {
        if (highScores[i].score > highScores[i - 1].score)
        {
            TIPO_SCORE temp = highScores[i];
            highScores[i] = highScores[i - 1];
            highScores[i - 1] = temp;
        }
    }
}

const TIPO_SCORE* GetHighScores(void)
{
    return highScores;
}