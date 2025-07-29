#ifndef SCREENS_H
#define SCREENS_H

// Nosso "mapa" de telas, agora com o Scoreboard.
typedef enum GameScreen {
    SCREEN_EXIT = -1,
    SCREEN_MENU,
    SCREEN_GAMEPLAY,
    SCREEN_GAMEOVER,
    SCREEN_WIN,
    SCREEN_SCOREBOARD // NOVA TELA
} GameScreen;

#endif // SCREENS_H