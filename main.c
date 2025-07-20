#include "raylib.h"
#include "menu_screen.h"
#include "gameplay_screen.h"
#include "gameover_screen.h"
#include "player.h" // <-- INCLUIR O CABEÇALHO DO JOGADOR

#define TOTAL_LEVELS 3

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");
    
    // MUDANÇA: Carrega os recursos do jogador uma única vez, antes de tudo
    LoadPlayerAssets();
    
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
                    InitPlayerState(); // <-- Reseta vidas/score aqui
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
                    if (currentLevel > TOTAL_LEVELS)
                    {
                        currentScreen = 0; 
                    }
                    // Se não, continua no estado de jogo (o loop vai rodar de novo)
                    // Não chamamos InitPlayerState() aqui, preservando o estado.
                }
            } break;

            case 2: // TELA DE FIM DE JOGO
            {
                int choice = RunGameOverScreen();
                if (choice == 1) { // Jogar novamente
                    currentLevel = 1;
                    InitPlayerState(); // <-- Reseta vidas/score aqui
                    currentScreen = 1;
                } else if (choice == 0) { // Sair
                    currentScreen = -1;
                }
            } break;
        }
    }

    // Descarrega os recursos do jogador no final
    UnloadPlayerAssets();
    CloseWindow();
    return 0;
}