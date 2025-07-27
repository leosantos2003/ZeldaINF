#include "raylib.h"
#include "menu_screen.h"
#include "gameplay_screen.h"
#include "gameover_screen.h"
#include "win_screen.h"
#include "player.h"
#include "renderer.h"
#include "scoreboard.h"
#include "scoreboard_screen.h" 

#define TOTAL_LEVELS 3

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");

    InitRenderer();
    LoadHighScores();
    SetTargetFPS(60);

    // Nossos estados de tela: 0:Menu, 1:Jogo, 2:GameOver, 3:Win, 4:EnterName, 5:Scoreboard
    int currentScreen = 0; 
    int currentLevel = 1;
    
    int finalScore = 0;
    int nextScreenAfterName = 0;

    while (currentScreen != -1 && !WindowShouldClose())
    {
        switch (currentScreen)
        {
            case 0: // TELA DE MENU
            {
                int menuChoice = RunMenuScreen();
                // Adicione esta linha para ver o valor que chegou aqui
                TraceLog(LOG_INFO, "MAIN DEBUG: menuChoice recebido com valor: %d", menuChoice);

                if (menuChoice == 1) { // Iniciar
                    currentLevel = 1;
                    InitPlayerState(); 
                    currentScreen = 1; 
                } 
                // A CONDIÇÃO CORRETA PARA O SCOREBOARD
                else if (menuChoice == 2) { // Scoreboard
                    currentScreen = 5; // Muda para a tela de scoreboard
                } 
                else if (menuChoice == 0) { // Sair
                    currentScreen = -1;
                }
            } break;
            
            case 1: // TELA DE JOGO
            {
                finalScore = RunGameplayScreen(currentLevel);
                
                if (finalScore == -1) {
                    currentScreen = -1;
                    break;
                }

                bool playerDied = (GetPlayer()->lives <= 0);
                bool playerWonGame = (!playerDied && currentLevel >= TOTAL_LEVELS);

                if (playerDied || playerWonGame)
                {
                    if (IsHighScore(finalScore))
                    {
                        nextScreenAfterName = playerDied ? 2 : 3;
                        currentScreen = 4;
                    }
                    else
                    {
                        currentScreen = playerDied ? 2 : 3;
                    }
                }
                else
                {
                    currentLevel++;
                }
            } break;

            case 2: // TELA DE FIM DE JOGO
            {
                int choice = RunGameOverScreen(finalScore);
                if (choice == 1) { 
                    currentLevel = 1;
                    InitPlayerState();
                    currentScreen = 1;
                } else if (choice == 0) { 
                    currentScreen = -1;
                }
            } break;

            case 3: // TELA DE VITÓRIA
            {
                int choice = RunWinScreen(finalScore);
                if (choice == 1) { 
                    currentLevel = 1;
                    InitPlayerState(); 
                    currentScreen = 1;
                } else if (choice == 0) { 
                    currentScreen = -1;
                }
            } break;
            
            //case 4: // TELA DE DIGITAR NOME
            //{
            //    RunEnterNameScreen(finalScore);
            //    currentScreen = nextScreenAfterName;
            //} break;

            case 5: // TELA DE SCOREBOARD
            {
                RunScoreboardScreen();
                currentScreen = 0; // Ao sair, sempre volta para o menu
            } break;
        }
    }

    UnloadRenderer();
    CloseWindow();
    
    return 0;
}