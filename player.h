#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define PLAYER_INVINCIBILITY_DURATION 1.0f

typedef struct {
    Vector2 gridPos;
    int orientation;
    int lives;
    int score;
    bool isInvincible;
    float invincibilityTimer;
} Player;

// MUDANÇAS: Funções de inicialização separadas
void LoadPlayerAssets(void);          // Carrega texturas (chamada uma vez)
void InitPlayerState(void);           // Reseta vidas e score (chamada no início de um novo jogo)
void SetPlayerStartPosition(Vector2 startPos); // Apenas posiciona o jogador no mapa

void UpdatePlayer(const char (*map)[24]);
void DrawPlayer(void);
void UnloadPlayerAssets(void);
Player *GetPlayer(void);

#endif // PLAYER_H