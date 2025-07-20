#include "player.h"
#include "level.h" // Incluído para TILE_SIZE e constantes do mapa
#include <math.h>

static Player player;
static Texture2D link_front, link_back, link_left, link_right;

void InitPlayer(Vector2 startPos)
{
    link_front = LoadTexture("resources/Link_front.png");
    link_back = LoadTexture("resources/Link_back.png");
    link_left = LoadTexture("resources/Link_left.png");
    link_right = LoadTexture("resources/Link_right.png");
    
    player.gridPos = startPos;
    player.lives = 3;
    player.score = 0;
    player.orientation = 0; // Baixo
    player.isInvincible = false;
    player.invincibilityTimer = 0;
}

void UpdatePlayer(const char (*map)[MAP_COLS])
{
    // Lógica de invencibilidade
    if (player.isInvincible)
    {
        player.invincibilityTimer -= GetFrameTime();
        if (player.invincibilityTimer <= 0)
        {
            player.isInvincible = false;
        }
    }

    // Lógica de movimento
    if (IsKeyPressed(KEY_D)) {
        player.orientation = 3; // Direita
        if (player.gridPos.x + 1 < MAP_COLS && map[(int)player.gridPos.y][(int)player.gridPos.x + 1] != 'P') player.gridPos.x++;
    } else if (IsKeyPressed(KEY_A)) {
        player.orientation = 2; // Esquerda
        if (player.gridPos.x - 1 >= 0 && map[(int)player.gridPos.y][(int)player.gridPos.x - 1] != 'P') player.gridPos.x--;
    } else if (IsKeyPressed(KEY_S)) {
        player.orientation = 0; // Baixo
        if (player.gridPos.y + 1 < MAP_ROWS && map[(int)player.gridPos.y + 1][(int)player.gridPos.x] != 'P') player.gridPos.y++;
    } else if (IsKeyPressed(KEY_W)) {
        player.orientation = 1; // Cima
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

void UnloadPlayerTextures(void)
{
    UnloadTexture(link_front);
    UnloadTexture(link_back);
    UnloadTexture(link_left);
    UnloadTexture(link_right);
}

Player *GetPlayer(void)
{
    return &player;
}