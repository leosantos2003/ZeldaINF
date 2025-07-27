#include "scoreboard_screen.h"
#include "scoreboard.h" // Para buscar os dados do ranking
#include "raylib.h"
#include "stdio.h"

void RunScoreboardScreen(void)
{
    // Pega um ponteiro para a lista de scores que já foi carregada na memória
    const TIPO_SCORE* highScores = GetHighScores();

    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        // Se o usuário pressionar ENTER ou ESC, sai da tela de scoreboard
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
        {
            return; // Volta para o main.c
        }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawText("MAIORES PONTUACOES", 180, 80, 70, GOLD);

            for (int i = 0; i < 5; i++)
            {
                // Formata o texto para um bom alinhamento
                char rankText[4];
                sprintf(rankText, "%d.", i + 1);
                
                char scoreText[20];
                sprintf(scoreText, "%d", highScores[i].score);

                DrawText(rankText, 300, 200 + i * 60, 40, LIGHTGRAY);
                DrawText(highScores[i].nome, 360, 200 + i * 60, 40, WHITE);
                DrawText(scoreText, 800, 200 + i * 60, 40, YELLOW);
            }

            DrawText("Pressione ENTER para voltar ao menu", 320, 600, 20, GRAY);

        EndDrawing();
    }
}