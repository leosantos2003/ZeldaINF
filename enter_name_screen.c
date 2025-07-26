#include "enter_name_screen.h"
#include "scoreboard.h"
#include "raylib.h"

void RunEnterNameScreen(int score)
{
    char name[20] = { 0 };
    int letterCount = 0;
    bool nameSubmitted = false;

    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        if (!nameSubmitted)
        {
            // Lógica de entrada de texto
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < 19))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0';
                    letterCount++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                if (letterCount > 0)
                {
                    AddHighScore(score, name);
                    SaveHighScores();
                    nameSubmitted = true;
                }
            }
        }
        else // Se o nome já foi submetido, espera qualquer tecla para sair
        {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
            {
                return; // Volta para o main.c
            }
        }
        
        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            if (!nameSubmitted)
            {
                DrawText("NOVO RECORDE!", 280, 150, 80, GOLD);
                DrawText("DIGITE SEU NOME:", 380, 280, 40, WHITE);
                DrawRectangle(380, 350, 440, 50, LIGHTGRAY);
                DrawRectangleLines(380, 350, 440, 50, DARKGRAY);
                DrawText(name, 390, 360, 40, MAROON);
                
                // Desenha um cursor piscando
                if ((int)(GetTime()*2.0f) % 2 == 0)
                {
                    DrawText("_", 390 + MeasureText(name, 40), 360, 40, MAROON);
                }
            }
            else // Mostra o novo ranking
            {
                DrawText("RANKING ATUALIZADO", 250, 80, 60, GOLD);
                const TIPO_SCORE* scores = GetHighScores();
                for (int i = 0; i < 5; i++)
                {
                    DrawText(TextFormat("%d.", i + 1), 300, 200 + i * 60, 40, WHITE);
                    DrawText(scores[i].nome, 350, 200 + i * 60, 40, WHITE);
                    DrawText(TextFormat("%d", scores[i].score), 800, 200 + i * 60, 40, WHITE);
                }
                DrawText("Pressione ENTER para continuar", 320, 600, 30, GRAY);
            }
            
        EndDrawing();
    }
}