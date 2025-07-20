#include "player.h"
#include "level.h"
#include <math.h>

static Player player;
static Texture2D link_front, link_back, link_left, link_right;

// ... (LoadPlayerAssets, InitPlayerState, SetPlayerStartPosition sem alterações) ...
void LoadPlayerAssets(void)
{
    link_front = LoadTexture("resources/Link_front.png");
    link_back = LoadTexture("resources/Link_back.png");
    link_left = LoadTexture("resources/Link_left.png");
    link_right = LoadTexture("resources/Link_right.png");
}

void InitPlayerState(void)
{
    player.lives = 3;
    player.score = 0;
    player.isInvincible = false;
    player.invincibilityTimer = 0;
    player.isDying = false;
}

void SetPlayerStartPosition(Vector2 startPos)
{
    player.gridPos = startPos;
    player.orientation = 0;
}


// ----- FUNÇÃO ATUALIZADA -----
void UpdatePlayer(const char (*map)[MAP_COLS])
{
    // A lógica dos timers de invencibilidade DEVE sempre rodar,
    // mesmo que o jogador esteja morrendo, para que a animação termine.
    if (player.isInvincible)
    {
        player.invincibilityTimer -= GetFrameTime();
        if (player.invincibilityTimer <= 0)
        {
            player.isInvincible = false;
        }
    }

    // Se o jogador está na animação de morte, ele não pode se mover.
    // Paramos a função aqui, DEPOIS de atualizar o timer.
    if (player.isDying) return;

    // Lógica de movimento (só é executada se o jogador não está morrendo)
    if (IsKeyPressed(KEY_D)) {
        player.orientation = 3;
        if (player.gridPos.x + 1 < MAP_COLS && map[(int)player.gridPos.y][(int)player.gridPos.x + 1] != 'P') player.gridPos.x++;
    } else if (IsKeyPressed(KEY_A)) {
        player.orientation = 2;
        if (player.gridPos.x - 1 >= 0 && map[(int)player.gridPos.y][(int)player.gridPos.x - 1] != 'P') player.gridPos.x--;
    } else if (IsKeyPressed(KEY_S)) {
        player.orientation = 0;
        if (player.gridPos.y + 1 < MAP_ROWS && map[(int)player.gridPos.y + 1][(int)player.gridPos.x] != 'P') player.gridPos.y++;
    } else if (IsKeyPressed(KEY_W)) {
        player.orientation = 1;
        if (player.gridPos.y - 1 >= 0 && map[(int)player.gridPos.y - 1][(int)player.gridPos.x] != 'P') player.gridPos.y--;
    }
}

void DrawPlayer(void)
{
    Texture2D playerTex;
    if(player.orientation == 0) playerTex = link_front;
    else if(player.orientation == 1) playerTex = link_back;
    else if(player.orientation == 2) playerTex = link_left;
    else playerTex = link_right;

    Vector2 playerPixelPos = { player.gridPos.x * TILE_SIZE, player.gridPos.y * TILE_SIZE + 60 };

    if (player.isInvincible)
    {
        if ((int)(player.invincibilityTimer * 10) % 2 != 0)
        {
            DrawTextureV(playerTex, playerPixelPos, WHITE);
        }
    }
    else
    {
        DrawTextureV(playerTex, playerPixelPos, WHITE);
    }
}

// Renomeada para corresponder ao novo nome da função de carregar
void UnloadPlayerAssets(void)
{
    UnloadTexture(link_front);
    UnloadTexture(link_back);
    UnloadTexture(link_left);
    UnloadTexture(link_right);
}

// NOVA FUNÇÃO: DamagePlayer
void DamagePlayer(Vector2 oldPos)
{
    // Só pode sofrer dano se não estiver invencível e não estiver já morrendo
    if (!player.isInvincible && !player.isDying)
    {
        player.lives--;
        player.isInvincible = true;
        player.invincibilityTimer = PLAYER_INVINCIBILITY_DURATION;
        
        // Recua para a posição anterior
        player.gridPos = oldPos;
        
        // Inverte a orientação
        switch(player.orientation)
        {
            case 0: player.orientation = 1; break; case 1: player.orientation = 0; break;
            case 2: player.orientation = 3; break; case 3: player.orientation = 2; break;
        }
        
        // Se as vidas acabaram, inicia o estado "morrendo"
        if (player.lives <= 0)
        {
            player.isDying = true;
        }
    }
}

// NOVA FUNÇÃO: IsPlayerDead
bool IsPlayerDead(void)
{
    // O jogador está morto APENAS se suas vidas acabaram E
    // ele não está mais invencível (a animação de piscar terminou).
    if (player.lives <= 0 && !player.isInvincible)
    {
        return true;
    }
    return false;
}

Player *GetPlayer(void)
{
    return &player;
}