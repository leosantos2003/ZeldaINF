#ifndef MONSTER_H
#define MONSTER_H

#include "raylib.h"

#define MAX_MONSTERS 10
#define MONSTER_DEATH_DURATION 0.5f

typedef struct {
    Vector2 gridPos;
    int orientation;
    bool active;
    bool isDying;
    float deathTimer;
} Monster;

void InitMonsters(void);
void AddMonster(Vector2 startPos);
void UpdateMonsters(const char (*map)[24]);
void DrawMonsters(void);
void UnloadMonsterTextures(void);
Monster *GetMonsters(void);
void DamageMonster(int monsterIndex);

// MUDANÇA: Substituímos GetTotalMonsterCount por uma função booleana mais inteligente
bool AreAnyMonstersLeft(void);

#endif // MONSTER_H