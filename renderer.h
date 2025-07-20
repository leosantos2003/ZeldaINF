#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "monster.h"

// Inicializa e carrega todas as texturas do jogo
void InitRenderer(void);

// Descarrega todas as texturas
void UnloadRenderer(void);

// Funções de desenho para cada tipo de entidade
void DrawGameLevel(void);
void DrawGamePlayer(const Player *player);
void DrawGameMonsters(const Monster monsters[]);
void DrawGameAttack(const Player *player, int orientation, int range);

#endif // RENDERER_H