#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "monster.h"

void InitRenderer(void);

void UnloadRenderer(void);

void DrawGameLevel(void);
void DrawGamePlayer(const Player *player);
void DrawGameMonsters(const Monster monsters[]);
void DrawGameAttack(const Player *player, int orientation, int range);

void DrawMenuCharacter(int x, int y);

#endif