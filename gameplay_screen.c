#include "gameplay_screen.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include <stdio.h>

#define ATTACK_DURATION 0.3f

// Variáveis estáticas para gerenciar o estado do ataque
static bool isAttacking = false;
static float attackTimer = 0.0f;
static int attackOrientation = 0;
static int currentAttackRange = 0; // Declaração da variável
static Texture2D attackTex_up, attackTex_down, attackTex_left, attackTex_right;

static void LoadGameplayResources(void)
{
    attackTex_up = LoadTexture("resources/Attack_up.png");
    attackTex_down = LoadTexture("resources/Attack_down.png");
    attackTex_left = LoadTexture("resources/Attack_left.png");
    attackTex_right = LoadTexture("resources/Attack_right.png");
}

static void UnloadLevelResources(void)
{
    UnloadLevel();
    UnloadMonsterTextures();
    UnloadTexture(attackTex_up);
    UnloadTexture(attackTex_down);
    UnloadTexture(attackTex_left);
    UnloadTexture(attackTex_right);
}

int RunGameplayScreen(int level)
{
    char fileName[20];
    sprintf(fileName, "nivel%d.txt", level);
    LoadLevel(fileName); 
    LoadGameplayResources();

    Player *player = GetPlayer();
    Monster *monsters = GetMonsters();
    
    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        UpdatePlayer(GetMap());
        UpdateMonsters(GetMap(), level);

        if (isAttacking)
        {
            attackTimer -= GetFrameTime();
            if (attackTimer <= 0) isAttacking = false;
        }

        if (IsKeyPressed(KEY_J) && !isAttacking)
        {
            isAttacking = true;
            attackTimer = ATTACK_DURATION;
            attackOrientation = player->orientation;

            currentAttackRange = 3; 
            if (level == 3)
            {
                currentAttackRange = 2;
            }

            for (int step = 1; step <= currentAttackRange; step++)
            {
                Vector2 targetPos = player->gridPos;
                if(attackOrientation == 0) targetPos.y += step;
                else if(attackOrientation == 1) targetPos.y -= step;
                else if(attackOrientation == 2) targetPos.x -= step;
                else if(attackOrientation == 3) targetPos.x += step;

                for (int i = 0; i < MAX_MONSTERS; i++)
                {
                    if (monsters[i].active && !monsters[i].isDying && monsters[i].gridPos.x == targetPos.x && monsters[i].gridPos.y == targetPos.y)
                    {
                        DamageMonster(i);
                        player->score += 100;
                    }
                }
            }
        }
        
        if (!player->isInvincible)
        {
            for (int i = 0; i < MAX_MONSTERS; i++)
            {
                if (monsters[i].active && !monsters[i].isDying && player->gridPos.x == monsters[i].gridPos.x && player->gridPos.y == monsters[i].gridPos.y)
                {
                    DamagePlayer(player->gridPos);
                }
            }
        }
        
        if (IsPlayerDead()) {
            UnloadLevelResources();
            return 0;
        }
        if (!AreAnyMonstersLeft()) {
            UnloadLevelResources();
            return 1;
        }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawLevel();
            DrawMonsters();
            DrawPlayer();
            
            if (isAttacking)
            {
                Texture2D swordTex;
                if(attackOrientation == 0) swordTex = attackTex_down;
                else if(attackOrientation == 1) swordTex = attackTex_up;
                else if(attackOrientation == 2) swordTex = attackTex_left;
                else swordTex = attackTex_right;

                for (int step = 1; step <= currentAttackRange; step++)
                {
                    Vector2 swordPos = player->gridPos;
                    if(attackOrientation == 0) swordPos.y += step;
                    else if(attackOrientation == 1) swordPos.y -= step;
                    else if(attackOrientation == 2) swordPos.x -= step;
                    else if(attackOrientation == 3) swordPos.x += step;

                    DrawTextureV(swordTex, (Vector2){swordPos.x * TILE_SIZE, swordPos.y * TILE_SIZE + 60}, WHITE);
                }
            }
            
            DrawRectangle(0, 0, GetScreenWidth(), 60, DARKGRAY);
            DrawText(TextFormat("VIDAS: %d", player->lives), 20, 15, 30, WHITE);
            DrawText(TextFormat("NIVEL: %d", level), GetScreenWidth() / 2 - 50, 15, 30, WHITE);
            DrawText(TextFormat("SCORE: %d", player->score), GetScreenWidth() - 200, 15, 30, WHITE);
            
        EndDrawing();
    }
    
    UnloadLevelResources();
    return -1;
}