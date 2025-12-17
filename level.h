#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

#define MAP_COLS 24
#define MAP_ROWS 16
#define TILE_SIZE 50

void LoadLevel(const char *fileName);
const char (*GetMap(void))[MAP_COLS];

#endif