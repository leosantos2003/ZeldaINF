#ifndef SCREENS_H
#define SCREENS_H

// Incluímos raylib aqui para que qualquer arquivo que inclua screens.h
// também tenha acesso às funções da raylib.
#include "raylib.h"

// Declaração da nossa função da tela de menu.
// Ela será definida em screens.c e chamada em main.c
// Ela retorna um inteiro para indicar a escolha do usuário (ex: 1 para Iniciar, 0 para Sair)
int RunMenuScreen(void);

#endif // SCREENS_H