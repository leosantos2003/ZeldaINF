#include "monster.h"
#include "level.h"
#include <stdlib.h>

// ... (variáveis estáticas sem alteração) ...
static Monster monsters[MAX_MONSTERS];
static int monsterCount = 0;
static float monsterMoveTimer = 0.0f;
static Texture2D enemy_front, enemy_back, enemy_left, enemy_right;


void InitMonsters(void)
{
    // ... (carregamento de texturas sem alteração) ...
    enemy_front = LoadTexture("resources/Enemy_front.png");
    enemy_back = LoadTexture("resources/Enemy_back.png");
    enemy_left = LoadTexture("resources/Enemy_left.png");
    enemy_right = LoadTexture("resources/Enemy_right.png");
    
    for(int i = 0; i < MAX_MONSTERS; i++)
    {
        monsters[i].active = false;
        monsters[i].isDying = false; // Inicializa o novo campo
    }
    monsterCount = 0;
}

void AddMonster(Vector2 startPos)
{
    if (monsterCount < MAX_MONSTERS)
    {
        monsters[monsterCount].gridPos = startPos;
        monsters[monsterCount].active = true;
        monsters[monsterCount].isDying = false; // Inicializa o novo campo
        monsters[monsterCount].orientation = 0;
        monsterCount++;
    }
}

void UpdateMonsters(const char (*map)[MAP_COLS])
{
    monsterMoveTimer += GetFrameTime();
    
    for (int i = 0; i < monsterCount; i++)
    {
        if (monsters[i].active)
        {
            // Se o monstro está morrendo, ele não se move
            if (monsters[i].isDying)
            {
                monsters[i].deathTimer -= GetFrameTime();
                if (monsters[i].deathTimer <= 0)
                {
                    monsters[i].active = false; // Agora sim, ele morre de verdade
                }
            }
            // Se está vivo e não está morrendo, ele se move
            else if (monsterMoveTimer >= 0.8f)
            {
                // ... (lógica de movimento aleatório, movida para dentro do loop) ...
                int move = rand() % 4;
                Vector2 targetPos = monsters[i].gridPos;
                if (move == 3 && targetPos.x + 1 < MAP_COLS && map[(int)targetPos.y][(int)targetPos.x + 1] != 'P') targetPos.x++;
                else if (move == 2 && targetPos.x - 1 >= 0 && map[(int)targetPos.y][(int)targetPos.x - 1] != 'P') targetPos.x--;
                else if (move == 0 && targetPos.y + 1 < MAP_ROWS && map[(int)targetPos.y + 1][(int)targetPos.x] != 'P') targetPos.y++;
                else if (move == 1 && targetPos.y - 1 >= 0 && map[(int)targetPos.y - 1][(int)targetPos.x] != 'P') targetPos.y--;
                monsters[i].gridPos = targetPos;
                monsters[i].orientation = move;
            }
        }
    }
    
    // Reseta o timer fora do loop para que todos os monstros se movam juntos
    if (monsterMoveTimer >= 0.8f) monsterMoveTimer = 0.0f;
}

void DrawMonsters(void)
{
    for (int i = 0; i < monsterCount; i++)
    {
        if (monsters[i].active)
        {
            // Define a textura normal do monstro
            Texture2D monsterTex;
            if(monsters[i].orientation == 0) monsterTex = enemy_front;
            else if(monsters[i].orientation == 1) monsterTex = enemy_back;
            else if(monsters[i].orientation == 2) monsterTex = enemy_left;
            else monsterTex = enemy_right;

            // Se está morrendo, pinta de vermelho. Senão, cor normal.
            Color tint = monsters[i].isDying ? RED : WHITE;

            DrawTextureV(monsterTex, (Vector2){ monsters[i].gridPos.x * TILE_SIZE, monsters[i].gridPos.y * TILE_SIZE + 60 }, tint);
        }
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

// ... (resto do arquivo monster.c sem alterações) ...
void UnloadMonsterTextures(void) { /* ... */ }
Monster *GetMonsters(void) { return monsters; }
int GetActiveMonsterCount(void) { /* ... */ }