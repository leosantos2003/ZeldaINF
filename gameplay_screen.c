#include "gameplay_screen.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include <stdio.h>

// Definições para o ataque
#define ATTACK_DURATION 0.3f

// Variáveis estáticas para gerenciar o estado e as texturas do ataque,
// pertencentes a este módulo "maestro".
static bool isAttacking = false;
static float attackTimer = 0.0f;
static int attackOrientation = 0;
static Texture2D attackTex_up, attackTex_down, attackTex_left, attackTex_right;

// NOVO: Contador de monstros restantes, pertencente a esta tela
static int monstersRemaining = 0;

// Função auxiliar para carregar recursos específicos da tela de jogo
static void LoadGameplayResources(void)
{
    attackTex_up = LoadTexture("resources/Attack_up.png");
    attackTex_down = LoadTexture("resources/Attack_down.png");
    attackTex_left = LoadTexture("resources/Attack_left.png");
    attackTex_right = LoadTexture("resources/Attack_right.png");
}

// ----- MUDANÇA AQUI -----
// Esta função agora descarrega apenas os recursos que são carregados a cada nível.
static void UnloadLevelResources(void)
{
    UnloadLevel();           // Descarrega chão e obstáculos do nível
    UnloadMonsterTextures(); // Descarrega texturas dos monstros do nível
    
    // Descarrega texturas do ataque (que são carregadas por esta tela)
    UnloadTexture(attackTex_up);
    UnloadTexture(attackTex_down);
    UnloadTexture(attackTex_left);
    UnloadTexture(attackTex_right);
    
    // A LINHA UnloadPlayerAssets() FOI REMOVIDA DAQUI
}


// Função que gerencia a tela de jogo, agora corrigida
int RunGameplayScreen(int level)
{
    // Inicialização
    char fileName[20];
    sprintf(fileName, "nivel%d.txt", level);
    LoadLevel(fileName); // Carrega o nível, que inicializa player e monstros
    
    LoadGameplayResources();
    
    // MUDANÇA: Inicializa nosso contador com o total de monstros do nível
    monstersRemaining = GetTotalMonsterCount();

    Player *player = GetPlayer();
    Monster *monsters = GetMonsters();
    
    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        Vector2 oldPlayerPos = player->gridPos;
        UpdatePlayer(GetMap());
        UpdateMonsters(GetMap());

        // Atualiza o timer de ataque se estiver atacando
        if (isAttacking)
        {
            attackTimer -= GetFrameTime();
            if (attackTimer <= 0) isAttacking = false;
        }

        // Lógica de Ataque (CORRIGIDA)
        if (IsKeyPressed(KEY_J) && !isAttacking)
        {
            isAttacking = true;
            attackTimer = ATTACK_DURATION;
            attackOrientation = player->orientation;

            // Verifica os 3 blocos à frente do jogador
            for (int step = 1; step <= 3; step++)
            {
                Vector2 targetPos = player->gridPos;
                if(attackOrientation == 0) targetPos.y += step;      // Baixo
                else if(attackOrientation == 1) targetPos.y -= step; // Cima
                else if(attackOrientation == 2) targetPos.x -= step; // Esquerda
                else if(attackOrientation == 3) targetPos.x += step; // Direita

                // Verifica se há um monstro no bloco alvo
                for (int i = 0; i < MAX_MONSTERS; i++)
                {
                    // Apenas monstros que não estão morrendo podem ser atingidos
                    if (monsters[i].active && !monsters[i].isDying && monsters[i].gridPos.x == targetPos.x && monsters[i].gridPos.y == targetPos.y)
                    {
                        DamageMonster(i);
                        player->score += 100;
                        monstersRemaining--; // MUDANÇA: Decrementa nosso contador
                    }
                }
            }
        }
        
        // Lógica de Colisão e Dano (sem alterações)
        if (!player->isInvincible)
        {
            for (int i = 0; i < MAX_MONSTERS; i++)
            {
                if (monsters[i].active && !monsters[i].isDying && player->gridPos.x == monsters[i].gridPos.x && player->gridPos.y == monsters[i].gridPos.y)
                {
                    player->lives--;
                    player->isInvincible = true;
                    player->invincibilityTimer = PLAYER_INVINCIBILITY_DURATION;
                    player->gridPos = oldPlayerPos;
                    switch(player->orientation)
                    {
                        case 0: player->orientation = 1; break; case 1: player->orientation = 0; break;
                        case 2: player->orientation = 3; break; case 3: player->orientation = 2; break;
                    }
                }
            }
        }

        // MUDANÇA: Condição de vitória agora usa nosso contador
        if (player->lives <= 0) {
            UnloadLevelResources();
            return 0;
        }
        if (monstersRemaining <= 0) {
            UnloadLevelResources();
            return 1;
        }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawLevel();
            DrawMonsters();
            DrawPlayer();
            
            // Desenho do Ataque da Espada (CORRIGIDO)
            if (isAttacking)
            {
                Texture2D swordTex;
                if(attackOrientation == 0) swordTex = attackTex_down;
                else if(attackOrientation == 1) swordTex = attackTex_up;
                else if(attackOrientation == 2) swordTex = attackTex_left;
                else swordTex = attackTex_right;

                for (int step = 1; step <= 3; step++)
                {
                    Vector2 swordPos = player->gridPos;
                    if(attackOrientation == 0) swordPos.y += step;
                    else if(attackOrientation == 1) swordPos.y -= step;
                    else if(attackOrientation == 2) swordPos.x -= step;
                    else if(attackOrientation == 3) swordPos.x += step;

                    DrawTextureV(swordTex, (Vector2){swordPos.x * TILE_SIZE, swordPos.y * TILE_SIZE + 60}, WHITE);
                }
            }
            
            // Desenha a UI (Barra de Status)
            DrawRectangle(0, 0, GetScreenWidth(), 60, DARKGRAY);
            DrawText(TextFormat("VIDAS: %d", player->lives), 20, 15, 30, WHITE);
            DrawText(TextFormat("NIVEL: %d", level), GetScreenWidth() / 2 - 50, 15, 30, WHITE);
            DrawText(TextFormat("SCORE: %d", player->score), GetScreenWidth() - 200, 15, 30, WHITE);
            
        EndDrawing();
    }
    
    UnloadLevelResources();
    return -1;
}