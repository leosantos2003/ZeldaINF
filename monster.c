#include "monster.h"
#include "level.h"
#include <stdlib.h>
#include <time.h>

static Monster monsters[MAX_MONSTERS];
static int monsterCount = 0;
static float monsterMoveTimer = 0.0f;

void InitMonsters(void)
{
    for(int i = 0; i < MAX_MONSTERS; i++)
    {
        monsters[i].active = false;
        monsters[i].isDying = false;
    }
    monsterCount = 0;
    srand(time(NULL));
}

void AddMonster(Vector2 startPos)
{
    if (monsterCount < MAX_MONSTERS)
    {
        monsters[monsterCount].gridPos = startPos;
        monsters[monsterCount].active = true;
        monsters[monsterCount].isDying = false;
        monsters[monsterCount].orientation = 0;
        monsterCount++;
    }
}

void UpdateMonsters(const char (*map)[MAP_COLS], int currentLevel)
{
    float moveDelay = 0.8f;
    switch (currentLevel)
    {
        case 2: moveDelay = 0.6f; break;
        case 3: moveDelay = 0.4f; break;
    }

    monsterMoveTimer += GetFrameTime();
    bool canMonstersMoveThisFrame = (monsterMoveTimer >= moveDelay);

    for (int i = 0; i < monsterCount; i++)
    {
        if (monsters[i].active)
        {
            if (monsters[i].isDying)
            {
                monsters[i].deathTimer -= GetFrameTime();
                if (monsters[i].deathTimer <= 0)
                {
                    monsters[i].active = false;
                }
            }
            else if (canMonstersMoveThisFrame)
            {
                int move = rand() % 4;
                Vector2 targetPos = monsters[i].gridPos;
                if (move == 3) targetPos.x++;
                else if (move == 2) targetPos.x--;
                else if (move == 0) targetPos.y++;
                else if (move == 1) targetPos.y--;

                bool isValidMove = false;
                if (targetPos.x >= 0 && targetPos.x < MAP_COLS && targetPos.y >= 0 && targetPos.y < MAP_ROWS)
                {
                    if (map[(int)targetPos.y][(int)targetPos.x] != 'P')
                    {
                        isValidMove = true;
                    }
                }

                if (isValidMove)
                {
                    bool isOccupied = false;
                    for (int j = 0; j < monsterCount; j++)
                    {
                        if (i != j && monsters[j].active && monsters[j].gridPos.x == targetPos.x && monsters[j].gridPos.y == targetPos.y)
                        {
                            isOccupied = true;
                            break;
                        }
                    }

                    if (!isOccupied)
                    {
                        monsters[i].gridPos = targetPos;
                        monsters[i].orientation = move;
                    }
                }
            }
        }
    }

    if (canMonstersMoveThisFrame)
    {
        monsterMoveTimer = 0.0f;
    }
}

void DamageMonster(int monsterIndex)
{
    if (monsterIndex >= 0 && monsterIndex < monsterCount && monsters[monsterIndex].active && !monsters[monsterIndex].isDying)
    {
        monsters[monsterIndex].isDying = true;
        monsters[monsterIndex].deathTimer = MONSTER_DEATH_DURATION;
    }
}

bool AreAnyMonstersLeft(void)
{
    for (int i = 0; i < monsterCount; i++)
    {
        if (monsters[i].active)
        {
            return true;
        }
    }
    return false;
}

Monster *GetMonsters(void)
{
    return monsters;
}