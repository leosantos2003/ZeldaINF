#include "raylib.h"
#include "menu_screen.h"      // <-- MUDOU
#include "gameplay_screen.h"  // <-- MUDOU

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");
    SetTargetFPS(60);

    int currentScreen = 0;

    while (currentScreen != -1 && !WindowShouldClose())
    {
        switch (currentScreen)
        {
            case 0: // TELA DE MENU
            {
                int menuChoice = RunMenuScreen();
                if (menuChoice == 1) {
                    currentScreen = 1; 
                }
                else if (menuChoice == 0) {
                    currentScreen = -1;
                }
            } break;
            
            case 1: // TELA DE JOGO
            {
                int gameResult = RunGameplayScreen();
                currentScreen = 0; // Sempre volta ao menu após o jogo terminar
            } break;
        }
    }

    CloseWindow();
    return 0;
}