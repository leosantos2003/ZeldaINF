#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdbool.h>

// Struct para uma entrada no placar
typedef struct {
    char nome[20];
    int score;
} TIPO_SCORE;

// Carrega os 5 maiores scores do arquivo ranking.bin para a memória
void LoadHighScores(void);

// Salva os 5 maiores scores da memória para o arquivo ranking.bin
void SaveHighScores(void);

// Verifica se uma pontuação é alta o suficiente para entrar no top 5
bool IsHighScore(int score);

// Adiciona um novo score ao ranking, mantendo a ordem decrescente
void AddHighScore(int score, const char *name);

// Função para permitir que outras telas leiam os scores
const TIPO_SCORE* GetHighScores(void);

#endif // SCOREBOARD_H