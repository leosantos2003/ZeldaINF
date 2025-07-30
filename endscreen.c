#include "endscreen.h"
#include "raylib.h"
#include "scoreboard.h"
#include "screens.h"

#include "endscreen.h"
#include "raylib.h"
#include "scoreboard.h"
#include "screens.h" 

GameScreen RunEndScreen(bool didWin, int finalScore)
{
    const char *titleText = didWin ? "Voce venceu!" : "Voce morreu!";
    Color titleColor = didWin ? GREEN : RED;

    const char *options[] = { "Jogar novamente", "Sair" };
    int currentOption = 0;

    int frameCounter = 0; // <- ADICIONE ESTA LINHA

    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        // Lógica de menu simples

        /*
        if (IsKeyPressed(KEY_DOWN)) currentOption = (currentOption + 1) % 2;
        if (IsKeyPressed(KEY_UP)) currentOption = (currentOption - 1 + 2) % 2;
        
        if (IsKeyPressed(KEY_ENTER))
        {
            if (currentOption == 0) return SCREEN_GAMEPLAY; // Jogar novamente
            if (currentOption == 1) return SCREEN_MENU; // Sair para o menu principal
        }
        */

        // --- ATUALIZAÇÃO ---
        // ACRESCENTE A VERIFICAÇÃO DO CONTADOR DE QUADROS
        if (frameCounter > 5) // Só começa a aceitar input após 5 quadros
        {
            if (IsKeyPressed(KEY_DOWN)) currentOption = (currentOption + 1) % 2;
            if (IsKeyPressed(KEY_UP)) currentOption = (currentOption - 1 + 2) % 2;
            
            if (IsKeyPressed(KEY_ENTER))
            {
                if (currentOption == 0) return SCREEN_GAMEPLAY; // Jogar novamente
                if (currentOption == 1) return SCREEN_MENU; // Sair para o menu principal
            }
        }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Mensagem principal
            DrawText(titleText, (GetScreenWidth() - MeasureText(titleText, 100)) / 2, 80, 100, titleColor);

            // Mostra o ranking
            DrawText("RANKING", (GetScreenWidth() - MeasureText("RANKING", 30)) / 2, 220, 30, GOLD);
            const TIPO_SCORE* scores = GetHighScores();
            
            /*
            for (int i = 0; i < 5; i++)
            {
                DrawText(TextFormat("%d. %.19s", i + 1, scores[i].nome), 350, 280 + i * 40, 20, WHITE);
                DrawText(TextFormat("%d", scores[i].score), 800, 280 + i * 40, 20, GOLD);
            }
            */

            // --- DEPOIS (com alinhamento de precisão) ---
            // Define uma área para o placar para garantir o alinhamento
            const int scoreboardWidth = 500;
            const int startX = (GetScreenWidth() - scoreboardWidth) / 2;
            const int endX = startX + scoreboardWidth;

            for (int i = 0; i < 5; i++)
            {
                // 1. Desenha a parte da ESQUERDA (ranking e nome), alinhada ao início da área.
                DrawText(TextFormat("%d. %.19s", i + 1, scores[i].nome), startX, 280 + i * 40, 20, WHITE);

                // 2. Formata, mede e desenha a parte da DIREITA (pontuação), alinhada ao final da área.
                const char* rightText = TextFormat("%d", scores[i].score);
                int rightTextWidth = MeasureText(rightText, 20);
                DrawText(rightText, endX - rightTextWidth, 280 + i * 40, 20, GOLD);
            }
            // FIM DA ALTERAÇÃO

            /*
            // Desenha as opções finais
            for (int i = 0; i < 2; i++)
            {
                Color color = (i == currentOption) ? YELLOW : WHITE;
                DrawText(options[i], (GetScreenWidth() - MeasureText(options[i], 40)) / 2, 550 + i * 50, 40, color);
            }
            */

            // --- DEPOIS ---
            // Desenha as opções finais com o indicador
            for (int i = 0; i < 2; i++)
            {
                Color color = (i == currentOption) ? YELLOW : WHITE;
                int fontSize = 40;
                const char* text = options[i];
                int textWidth = MeasureText(text, fontSize);
                int posX = (GetScreenWidth() - textWidth) / 2;
                int posY = 550 + i * 50;

                // Desenha o texto da opção ("Jogar novamente" ou "Sair")
                DrawText(text, posX, posY, fontSize, color);

                // Se esta for a opção selecionada, desenha o indicador
                if (i == currentOption)
                {
                    DrawText("-", posX - 50, posY, fontSize, RED);
                }
            }
            // FIM DA ALTERAÇÃO
            
        EndDrawing();

        frameCounter++; // <- ADICIONE ESTA LINHA NO FINAL DO LAÇO
    }
    
    return SCREEN_MENU; // Padrão
}