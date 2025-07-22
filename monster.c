#include "monster.h"
#include "level.h"
#include <stdlib.h>
#include <time.h>

static Monster monsters[MAX_MONSTERS];
static int monsterCount = 0;
static float monsterMoveTimer = 0.0f;

// A função agora apenas reseta o estado lógico, sem carregar texturas
void InitMonsters(void)
{
    for(int i = 0; i < MAX_MONSTERS; i++)
    {
        monsters[i].active = false;
        monsters[i].isDying = false;
    }
    monsterCount = 0;
    srand(time(NULL)); // Garante que o movimento aleatório seja diferente a cada jogo
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

// ----- FUNÇÃO ATUALIZADA E REESTRUTURADA -----
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
                // 1. Calcula para onde o monstro 'i' QUER se mover
                int move = rand() % 4;
                Vector2 targetPos = monsters[i].gridPos;
                if (move == 3) targetPos.x++;      // Direita
                else if (move == 2) targetPos.x--; // Esquerda
                else if (move == 0) targetPos.y++; // Baixo
                else if (move == 1) targetPos.y--; // Cima

                // 2. Verifica se o movimento é válido (dentro do mapa e não é um obstáculo)
                bool isValidMove = false;
                if (targetPos.x >= 0 && targetPos.x < MAP_COLS && targetPos.y >= 0 && targetPos.y < MAP_ROWS)
                {
                    if (map[(int)targetPos.y][(int)targetPos.x] != 'P')
                    {
                        isValidMove = true;
                    }
                }

                // 3. Se for válido, agora verifica se não está ocupado por outro monstro
                if (isValidMove)
                {
                    bool isOccupied = false;
                    // Loop aninhado para verificar a posição contra todos os outros monstros
                    for (int j = 0; j < monsterCount; j++)
                    {
                        // Um monstro não pode colidir consigo mesmo (i != j)
                        // E só verifica contra outros monstros ativos
                        if (i != j && monsters[j].active && monsters[j].gridPos.x == targetPos.x && monsters[j].gridPos.y == targetPos.y)
                        {
                            isOccupied = true;
                            break; // Encontrou um monstro, não precisa continuar procurando
                        }
                    }

                    // 4. Se o movimento é válido E o local não está ocupado, move o monstro
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