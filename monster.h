#ifndef MONSTER_H
#define MONSTER_H

#include "raylib.h"

#define MAX_MONSTERS 10
#define MONSTER_DEATH_DURATION 0.5f // Duração do estado "morrendo"

typedef struct {
    Vector2 gridPos;
    int orientation;
    bool active;
    bool isDying;           // NOVO: Flag para o estado "morrendo"
    float deathTimer;       // NOVO: Temporizador para a morte
} Monster;

void InitMonsters(void);
void AddMonster(Vector2 startPos);
void UpdateMonsters(const char (*map)[24]);
void DrawMonsters(void);
void UnloadMonsterTextures(void);
Monster *GetMonsters(void);
int GetActiveMonsterCount(void);
void DamageMonster(int monsterIndex); // NOVO: Função para iniciar a sequência de morte

#endif // MONSTER_H