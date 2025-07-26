#include "scoreboard.h"
#include <stdio.h>
#include <string.h>

#define MAX_SCORES 5
#define SCORE_FILE "ranking.bin"

// Array estático para manter os scores em memória durante o jogo
static TIPO_SCORE highScores[MAX_SCORES];

void LoadHighScores(void)
{
    FILE *file = fopen(SCORE_FILE, "rb"); // "rb" = read binary
    
    // Se o arquivo não existe, cria um placar zerado
    if (file == NULL)
    {
        for (int i = 0; i < MAX_SCORES; i++)
        {
            strcpy(highScores[i].nome, "NINGUEM");
            highScores[i].score = 0;
        }
        return;
    }
    
    // Lê o array de 5 structs diretamente do arquivo
    fread(highScores, sizeof(TIPO_SCORE), MAX_SCORES, file);
    fclose(file);
}

void SaveHighScores(void)
{
    FILE *file = fopen(SCORE_FILE, "wb"); // "wb" = write binary
    if (file == NULL) return;
    
    // Escreve o array de 5 structs diretamente no arquivo
    fwrite(highScores, sizeof(TIPO_SCORE), MAX_SCORES, file);
    fclose(file);
}

bool IsHighScore(int score)
{
    // Se a pontuação for maior que a última do ranking, já é um recorde
    return (score > highScores[MAX_SCORES - 1].score);
}

void AddHighScore(int score, const char *name)
{
    // Coloca o novo score na última posição
    highScores[MAX_SCORES - 1].score = score;
    strncpy(highScores[MAX_SCORES - 1].nome, name, 19);
    highScores[MAX_SCORES - 1].nome[19] = '\0';

    // "Sobe" o novo score para sua posição correta, mantendo a ordem
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