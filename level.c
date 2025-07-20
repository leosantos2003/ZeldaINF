#include "level.h"
#include "player.h"
#include "monster.h"
#include <stdio.h>

static char map[MAP_ROWS][MAP_COLS] = { 0 };

// A função agora apenas lê o arquivo e popula as entidades
void LoadLevel(const char *fileName)
{
    InitMonsters(); // Reseta a lista de monstros para o novo nível

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
                SetPlayerStartPosition((Vector2){c, r});
            }
            else if (tile == 'M')
            {
                AddMonster((Vector2){c, r});
            }
        }
    }
    fclose(file);
}

const char (*GetMap(void))[MAP_COLS]
{
    return map;
}