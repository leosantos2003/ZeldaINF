#include "gameplay_screen.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include "combat.h" // Novo include
#include "ui.h"     // Novo include
#include <stdio.h>

#define ATTACK_DURATION 0.3f

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
        Vector2 oldPlayerPos = player->gridPos;
        UpdatePlayer(GetMap());
        UpdateMonsters(GetMap(), level);
        
        // Chama os sistemas de combate
        ProcessPlayerAttack(player, monsters, level);
        ProcessCollisions(player, monsters, oldPlayerPos);
        
        // --- VERIFICAÇÃO DE ESTADO ---
        if (IsPlayerDead()) { UnloadLevelResources(); return 0; }
        if (!AreAnyMonstersLeft()) { UnloadLevelResources(); return 1; }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawLevel();
            DrawMonsters();
            DrawPlayer();

            // Pergunta ao módulo de combate se deve desenhar o ataque
            int attackOrientation, attackRange;
            if (IsPlayerAttacking(&attackOrientation, &attackRange))
            {
                // Define a textura da espada baseada na orientação recebida
                Texture2D swordTex;
                if(attackOrientation == 0) swordTex = attackTex_down;
                else if(attackOrientation == 1) swordTex = attackTex_up;
                else if(attackOrientation == 2) swordTex = attackTex_left;
                else swordTex = attackTex_right;

                // Loop para desenhar uma espada em cada bloco do alcance do ataque
                for (int step = 1; step <= attackRange; step++)
                {
                    // Pega a posição atual do jogador para calcular a posição da espada
                    Vector2 swordPos = player->gridPos;
                    
                    // Calcula a posição do bloco da espada
                    if(attackOrientation == 0) swordPos.y += step;      // Baixo
                    else if(attackOrientation == 1) swordPos.y -= step; // Cima
                    else if(attackOrientation == 2) swordPos.x -= step; // Esquerda
                    else if(attackOrientation == 3) swordPos.x += step; // Direita

                    // Desenha a textura da espada na posição calculada em pixels
                    DrawTextureV(swordTex, (Vector2){swordPos.x * TILE_SIZE, swordPos.y * TILE_SIZE + 60}, WHITE);
                }
            }
            
            // Chama o sistema de UI
            DrawGameplayUI(player, level);
            
        EndDrawing();
    }
    
    UnloadLevelResources();
    return -1;
}