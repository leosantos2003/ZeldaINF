#include "raylib.h"
#include "screens.h" // Incluímos o nosso módulo de telas

//------------------------------------------------------------------------------------
// Programa Principal
//------------------------------------------------------------------------------------
int main(void)
{
    // ---- INICIALIZAÇÃO ----
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");
    SetTargetFPS(60);

    // TODO: Aqui podemos definir um estado de jogo (ex: MENU, GAMEPLAY, SCOREBOARD)
    
    // Por enquanto, apenas chamamos a tela de menu
    int menuChoice = RunMenuScreen();

    // Com base na escolha do menu, decidimos o que fazer
    switch (menuChoice)
    {
        case 1: // Iniciar Jogo
            // TODO: Chamar a função RunGameplayScreen()
            TraceLog(LOG_INFO, "O JOGO DEVERIA INICIAR AGORA...");
            break;
        case 2: // Scoreboard
            // TODO: Chamar a função RunScoreboardScreen()
            TraceLog(LOG_INFO, "O SCOREBOARD DEVERIA APARECER AGORA...");
            break;
        case 0: // Sair
            // Não faz nada, o jogo vai fechar naturalmente
            break;
    }

    // ---- FINALIZAÇÃO ----
    CloseWindow();
    return 0;
}