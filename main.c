#include "raylib.h"
#include "menu_screen.h"
#include "gameplay_screen.h"
#include "gameover_screen.h"
#include "win_screen.h"
#include "player.h"   // Ainda necessário para chamar InitPlayerState
#include "renderer.h" // O novo módulo de renderização

#define TOTAL_LEVELS 3

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");

    // Inicializa o módulo que carrega TODAS as texturas e recursos visuais do jogo
    InitRenderer();
    
    SetTargetFPS(60);

    int currentScreen = 0; 
    int currentLevel = 1;

    // O loop principal permanece o mesmo, gerenciando o fluxo entre as telas
    while (currentScreen != -1 && !WindowShouldClose())
    {
        switch (currentScreen)
        {
            case 0: // TELA DE MENU
            {
                int menuChoice = RunMenuScreen();
                if (menuChoice == 1) { // Iniciar
                    currentLevel = 1;
                    // Reseta o estado do jogador para um novo jogo
                    InitPlayerState(); 
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
                    // MUDANÇA: Se o jogador venceu o último nível...
                    if (currentLevel > TOTAL_LEVELS)
                    {
                        currentScreen = 3; // ...vai para a tela de Vitória!
                    }
                    // Se não, continua no estado de jogo (o loop vai rodar de novo com o novo nível).
                }
            } break;

            case 2: // TELA DE FIM DE JOGO
            {
                int choice = RunGameOverScreen();
                if (choice == 1) { // Jogar novamente
                    currentLevel = 1;
                    // Reseta o estado do jogador para um novo jogo
                    InitPlayerState();
                    currentScreen = 1;
                } else if (choice == 0) { // Sair
                    currentScreen = -1;
                }
            } break;

            // ---- NOVO CASE PARA A TELA DE VITÓRIA ----
            case 3: // TELA DE VITÓRIA
            {
                int choice = RunWinScreen();
                if (choice == 1) { // Jogar novamente
                    currentLevel = 1;
                    InitPlayerState(); // Reseta o estado do jogador
                    currentScreen = 1;
                } else if (choice == 0) { // Sair
                    currentScreen = -1; // Volta para o menu principal
                }
            } break;
        }
    }

    // Descarrega todos os recursos visuais que foram carregados pelo renderer
    UnloadRenderer();
    CloseWindow();
    
    return 0;
}