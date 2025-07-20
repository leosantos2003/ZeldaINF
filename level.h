#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

// Constantes do mapa agora pertencem a este módulo
#define MAP_COLS 24
#define MAP_ROWS 16
#define TILE_SIZE 50

void LoadLevel(const char *fileName);
void UnloadLevel(void);
void DrawLevel(void);
const char (*GetMap(void))[MAP_COLS]; // Função para dar acesso ao mapa a outros módulos

#endif // LEVEL_H