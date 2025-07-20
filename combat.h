#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"
#include "monster.h"

// Processa o ataque do jogador, verificando se algum monstro foi atingido
void ProcessPlayerAttack(Player *player, Monster monsters[], int level);

// Processa colisões entre o jogador e os monstros
void ProcessCollisions(Player *player, Monster monsters[], Vector2 oldPlayerPos);

// Nova função para o desenho
bool IsPlayerAttacking(int *orientation, int *range);

#endif // COMBAT_H