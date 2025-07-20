#include "raylib.h"
#include "menu_screen.h"
#include "gameplay_screen.h"
#include "gameover_screen.h"

#define TOTAL_LEVELS 3 // MUDANÇA: Agora temos 3 níveis

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");
    SetTargetFPS(60);

    int currentScreen = 0; 
    int currentLevel = 1;

    while (currentScreen != -1 && !WindowShouldClose())
    {
        switch (currentScreen)
        {
            case 0: // TELA DE MENU
            {
                int menuChoice = RunMenuScreen();
                if (menuChoice == 1) { // Iniciar
                    currentLevel = 1;
                    currentScreen = 1; 
                } else if (menuChoice == 0) { // Sair
                    currentScreen = -1;
                }
            } break;
            
            case 1: // TELA DE JOGO
            {
                int gameResult = RunGameplayScreen(currentLevel);
                
                if (gameResult == 0) { // Perdeu
                    currentScreen = 2;
                } 
                else if (gameResult == 1) { // Ganhou
                    currentLevel++;
                    // Se o jogador venceu o último nível...
                    if (currentLevel > TOTAL_LEVELS)
                    {
                        // TODO: Implementar uma tela de "Você Venceu!"
                        // Por enquanto, apenas voltamos ao menu principal.
                        currentScreen = 0; 
                    }
                    // Se não, o jogo continua no estado '1' (Jogo),
                    // e o loop principal irá chamar RunGameplayScreen com o novo currentLevel.
                }
            } break;

            case 2: // TELA DE FIM DE JOGO
            {
                int choice = RunGameOverScreen();
                if (choice == 1) { // Jogar novamente
                    currentLevel = 1;
                    currentScreen = 1;
                } else if (choice == 0) { // Sair
                    currentScreen = -1;
                }
            } break;
        }
    }

    CloseWindow();
    return 0;
}