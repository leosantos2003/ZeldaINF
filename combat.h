#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"
#include "monster.h"

void ProcessPlayerAttack(Player *player, Monster monsters[], int level);

void ProcessCollisions(Player *player, Monster monsters[], Vector2 oldPlayerPos);

bool IsPlayerAttacking(int *orientation, int *range);

#endif