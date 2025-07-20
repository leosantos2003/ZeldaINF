#include "raylib.h"
#include "menu_screen.h"
#include "gameplay_screen.h"
#include "gameover_screen.h" // <-- INCLUIR NOVO CABEÇALHO

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");
    SetTargetFPS(60);

    // Nossos estados de tela: 0:Menu, 1:Jogo, 2:Fim de Jogo
    int currentScreen = 0; 

    while (currentScreen != -1 && !WindowShouldClose())
    {
        switch (currentScreen)
        {
            case 0: // TELA DE MENU
            {
                int menuChoice = RunMenuScreen();
                if (menuChoice == 1) { // Iniciar
                    currentScreen = 1; 
                } else if (menuChoice == 0) { // Sair
                    currentScreen = -1;
                }
            } break;
            
            case 1: // TELA DE JOGO
            {
                int gameResult = RunGameplayScreen();
                if (gameResult == 0) { // Perdeu
                    currentScreen = 2; // Mudar para a tela de Fim de Jogo
                } else if (gameResult == 1) { // Ganhou
                    // TODO: Mudar para tela de vitória ou próximo nível
                    currentScreen = 0; // Por enquanto, volta ao menu
                }
            } break;

            // ---- NOVO CASE PARA A TELA DE FIM DE JOGO ----
            case 2: // TELA DE FIM DE JOGO
            {
                int choice = RunGameOverScreen();
                if (choice == 1) { // Jogar novamente
                    currentScreen = 1;
                } else if (choice == 0) { // Sair
                    currentScreen = -1; // Volta para o menu principal
                }
            } break;
        }
    }

    CloseWindow();
    return 0;
}