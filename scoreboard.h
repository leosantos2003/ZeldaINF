#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdbool.h>

typedef struct {
    char nome[20];
    int score;
} TIPO_SCORE;

void LoadHighScores(void);

void SaveHighScores(void);

bool IsHighScore(int score);

void AddHighScore(int score, const char *name);

const TIPO_SCORE* GetHighScores(void);

#endif