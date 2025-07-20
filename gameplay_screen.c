#include "gameplay_screen.h"
#include "level.h"
#include "player.h"
#include "monster.h"

#define ATTACK_DURATION 0.3f // Duração do visual da espada na tela

// Variáveis estáticas para controlar o ataque
static bool isAttacking = false;
static float attackTimer = 0.0f;
static int attackOrientation = 0;
static Texture2D attackTex_up, attackTex_down, attackTex_left, attackTex_right;

// Função auxiliar para inicializar/resetar a tela de jogo
static void InitGameplay(void)
{
    LoadLevel("nivel1.txt"); // Carrega mapa, que inicializa player e monstros
    isAttacking = false;
    attackTimer = 0.0f;

    // Carrega texturas de ataque
    attackTex_up = LoadTexture("resources/Attack_up.png");
    attackTex_down = LoadTexture("resources/Attack_down.png");
    attackTex_left = LoadTexture("resources/Attack_left.png");
    attackTex_right = LoadTexture("resources/Attack_right.png");
}

// Função auxiliar para descarregar recursos
static void UnloadGameplay(void)
{
    UnloadLevel();
    UnloadPlayerTextures();
    UnloadMonsterTextures();
    UnloadTexture(attackTex_up);
    UnloadTexture(attackTex_down);
    UnloadTexture(attackTex_left);
    UnloadTexture(attackTex_right);
}


// Função que gerencia a tela de jogo
int RunGameplayScreen(void)
{
    InitGameplay();
    Player *player = GetPlayer();
    Monster *monsters = GetMonsters();
    
    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        Vector2 oldPlayerPos = player->gridPos;
        UpdatePlayer(GetMap());
        UpdateMonsters(GetMap());

        // Lógica de ataque
        if (isAttacking)
        {
            attackTimer -= GetFrameTime();
            if (attackTimer <= 0) isAttacking = false;
        }

        if (IsKeyPressed(KEY_J) && !isAttacking)
        {
            isAttacking = true;
            attackTimer = ATTACK_DURATION;
            attackOrientation = player->orientation; // Trava a orientação do ataque

            // Verifica os 3 blocos à frente
            for (int step = 1; step <= 3; step++)
            {
                Vector2 targetPos = player->gridPos;
                if(attackOrientation == 0) targetPos.y += step; // Baixo
                else if(attackOrientation == 1) targetPos.y -= step; // Cima
                else if(attackOrientation == 2) targetPos.x -= step; // Esquerda
                else if(attackOrientation == 3) targetPos.x += step; // Direita

                // Verifica se há um monstro no bloco alvo
                for (int i = 0; i < MAX_MONSTERS; i++)
                {
                    if (monsters[i].active && !monsters[i].isDying && monsters[i].gridPos.x == targetPos.x && monsters[i].gridPos.y == targetPos.y)
                    {
                        DamageMonster(i); // Diz ao módulo de monstro para iniciar a morte
                        player->score += 100;
                    }
                }
            }
        }
        
        // ... (Lógica de Colisão e Dano sem alterações) ...
        if (!player->isInvincible) { /* ... */ }


        // Condições de fim de jogo
        if (player->lives <= 0) {
            UnloadGameplay();
            return 0; // Game Over
        }
        if (GetActiveMonsterCount() == 0) {
            UnloadGameplay();
            return 1; // Vitória
        }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawLevel();
            DrawMonsters();
            DrawPlayer();

            // Desenha o ataque da espada
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
            
            // Barra de Status
            DrawRectangle(0, 0, GetScreenWidth(), 60, DARKGRAY);
            DrawText(TextFormat("VIDAS: %d", player->lives), 20, 15, 30, WHITE);
            DrawText("NIVEL: 1", GetScreenWidth() / 2 - 50, 15, 30, WHITE);
            DrawText(TextFormat("SCORE: %d", player->score), GetScreenWidth() - 200, 15, 30, WHITE);
            
        EndDrawing();
    }
    
    UnloadGameplay();
    return -1;
}