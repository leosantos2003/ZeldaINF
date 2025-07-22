#include "player.h"
#include "level.h" // Incluído para as constantes do mapa (MAP_COLS, etc)
#include <math.h>

static Player player;

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

void UpdatePlayer(const char (*map)[MAP_COLS])
{
    // A lógica dos timers de invencibilidade DEVE sempre rodar
    if (player.isInvincible)
    {
        player.invincibilityTimer -= GetFrameTime();
        if (player.invincibilityTimer <= 0)
        {
            player.isInvincible = false;
        }
    }

    // Se o jogador está na animação de morte, ele não pode se mover
    if (player.isDying) return;

    // Lógica de movimento
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

void DamagePlayer(Vector2 oldPos)
{
    if (!player.isInvincible && !player.isDying)
    {
        player.lives--;
        player.isInvincible = true;
        player.invincibilityTimer = PLAYER_INVINCIBILITY_DURATION;
        player.gridPos = oldPos;
        
        switch(player.orientation)
        {
            case 0: player.orientation = 1; break; case 1: player.orientation = 0; break;
            case 2: player.orientation = 3; break; case 3: player.orientation = 2; break;
        }
        
        if (player.lives <= 0)
        {
            player.isDying = true;
        }
    }
}

bool IsPlayerDead(void)
{
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