#include "level.h"
#include "player.h"   // O level precisa saber sobre o player para inicializá-lo
#include "monster.h"  // E também sobre os monstros

#include <stdio.h>

// O mapa e as texturas do cenário são privados a este módulo
static char map[MAP_ROWS][MAP_COLS] = { 0 };
static Texture2D groundTexture;
static Texture2D obstacleTexture;

void LoadLevel(const char *fileName)
{
    // Carrega texturas
    groundTexture = LoadTexture("resources/Ground.png");
    obstacleTexture = LoadTexture("resources/Obstacle.png");
    
    // Zera os monstros antes de carregar o novo mapa
    InitMonsters();

    FILE *file = fopen(fileName, "r");
    if (file == NULL) return;

    for (int r = 0; r < MAP_ROWS; r++)
    {
        for (int c = 0; c < MAP_COLS; c++)
        {
            char tile = fgetc(file);
            while (tile == '\n' || tile == '\r') tile = fgetc(file);
            
            map[r][c] = tile;
            
            if (tile == 'J')
            {
                InitPlayer((Vector2){c, r}); // Passa a posição inicial para o módulo do player
            }
            else if (tile == 'M')
            {
                AddMonster((Vector2){c, r}); // Adiciona um monstro na posição
            }
        }
    }
    fclose(file);
}

void UnloadLevel(void)
{
    UnloadTexture(groundTexture);
    UnloadTexture(obstacleTexture);
}

void DrawLevel(void)
{
    for (int r = 0; r < MAP_ROWS; r++)
    {
        for (int c = 0; c < MAP_COLS; c++)
        {
            Vector2 tilePos = { (float)c * TILE_SIZE, (float)r * TILE_SIZE + 60 }; // 60 é a altura da status bar
            
            if (map[r][c] == 'P')
            {
                DrawTextureV(obstacleTexture, tilePos, WHITE);
            }
            else
            {
                DrawTextureV(groundTexture, tilePos, WHITE);
            }
        }
    }
}

const char (*GetMap(void))[MAP_COLS]
{
    return map;
}