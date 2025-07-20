#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define PLAYER_INVINCIBILITY_DURATION 1.5f

typedef struct {
    Vector2 gridPos;
    int orientation;
    int lives;
    int score;
    bool isInvincible;
    float invincibilityTimer;
} Player;

void InitPlayer(Vector2 startPos);
void UpdatePlayer(const char (*map)[24]); // Precisa do mapa para verificar colisões
void DrawPlayer(void);
void UnloadPlayerTextures(void);
Player *GetPlayer(void); // Função para dar acesso aos dados do jogador

#endif // PLAYER_H