#ifndef MONSTER_H
#define MONSTER_H

#include "raylib.h"

#define MAX_MONSTERS 20
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
void UpdateMonsters(const char (*map)[24], int currentLevel);
Monster *GetMonsters(void);
void DamageMonster(int monsterIndex);
bool AreAnyMonstersLeft(void);

#endif