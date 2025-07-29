#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "raylib.h"
#include "screens.h" 
#include <stdbool.h>

// Roda a tela final, recebendo um booleano para saber se é vitória ou derrota
GameScreen RunEndScreen(bool didWin, int finalScore);

#endif // ENDSCREEN_H