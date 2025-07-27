#include "raylib.h"
#include "menu_screen.h"
#include "gameplay_screen.h"
#include "gameover_screen.h"
#include "win_screen.h"
#include "player.h"
#include "renderer.h"
#include "scoreboard.h"
#include "enter_name_screen.h"

#define TOTAL_LEVELS 3

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");

    InitRenderer();
    LoadHighScores();
    SetTargetFPS(60);

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
                if (menuChoice == 1) { 
                    currentLevel = 1;
                    InitPlayerState(); 
                    currentScreen = 1; 
                } else if (menuChoice == 0) { 
                    currentScreen = -1;
                }
            } break;
            
            case 1: // TELA DE JOGO
            {
                finalScore = RunGameplayScreen(currentLevel);
                
                if (finalScore == -1) { // Usuário fechou a janela
                    currentScreen = -1;
                    break;
                }

                bool playerDied = (GetPlayer()->lives <= 0);
                bool playerWonGame = (!playerDied && currentLevel >= TOTAL_LEVELS);

                // A verificação de recorde SÓ acontece se o jogo terminou (morte ou vitória final)
                if (playerDied || playerWonGame)
                {
                    if (IsHighScore(finalScore))
                    {
                        // Define para qual tela ir DEPOIS de digitar o nome
                        nextScreenAfterName = playerDied ? 2 : 3; // 2=GameOver, 3=Win
                        currentScreen = 4; // Vai para a tela de digitar nome
                    }
                    else
                    {
                        // Sem recorde, vai direto para a tela final apropriada
                        currentScreen = playerDied ? 2 : 3;
                    }
                }
                else // Se o jogo não terminou, o jogador apenas passou de nível
                {
                    currentLevel++;
                    // O currentScreen continua '1', então o loop irá chamar RunGameplayScreen novamente com o novo nível
                }
            } break;

            case 2: // TELA DE FIM DE JOGO
            {
                int choice = RunGameOverScreen();
                if (choice == 1) { 
                    currentLevel = 1;
                    InitPlayerState();
                    currentScreen = 1;
                } else if (choice == 0) { 
                    currentScreen = -1; //SAIR*****
                }
            } break;

            case 3: // TELA DE VITÓRIA
            {
                int choice = RunWinScreen();
                if (choice == 1) { 
                    currentLevel = 1;
                    InitPlayerState(); 
                    currentScreen = 1;
                } else if (choice == 0) { 
                    currentScreen = -1; //SAIR*****
                }
            } break;
            
            case 4: // TELA DE DIGITAR NOME
            {
                RunEnterNameScreen(finalScore);
                currentScreen = nextScreenAfterName; // Vai para a tela final que foi guardada
            } break;
        }
    }

    UnloadRenderer();
    CloseWindow();
    
    return 0;
}