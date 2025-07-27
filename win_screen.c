#include "win_screen.h"
#include "raylib.h"
#include "scoreboard.h"

int RunWinScreen(int finalScore)
{
    bool isNewHighScore = IsHighScore(finalScore);
    char name[20] = { 0 };
    int letterCount = 0;
    bool nameSubmitted = false;

    const char *options[] = { "Jogar novamente", "Sair" };
    int currentOption = 0;

    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO --- (Idêntica à da tela de Game Over)
        if (isNewHighScore && !nameSubmitted)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < 19))
                {
                    name[letterCount++] = (char)key;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && letterCount > 0)
            {
                AddHighScore(finalScore, name);
                SaveHighScores();
                nameSubmitted = true;
            }
        }
        else
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            if (IsKeyPressed(KEY_DOWN)) currentOption = (currentOption + 1) % 2;
            if (IsKeyPressed(KEY_UP)) currentOption = (currentOption - 1 + 2) % 2;
            if (IsKeyPressed(KEY_ENTER)) return (currentOption == 0) ? 1 : 0;
        }

        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            // MUDANÇA: Mensagem de vitória em verde
            DrawText("Voce venceu!", (GetScreenWidth() - MeasureText("Voce venceu!", 100)) / 2, 80, 100, GREEN);

            // O resto da lógica de desenho é idêntica à da tela de Game Over
            if (isNewHighScore && !nameSubmitted)
            {
                DrawText("NOVO RECORDE!", (GetScreenWidth() - MeasureText("NOVO RECORDE!", 40)) / 2, 220, 40, GOLD);
                DrawText("DIGITE SEU NOME:", (GetScreenWidth() - MeasureText("DIGITE SEU NOME:", 20)) / 2, 300, 20, LIGHTGRAY);
                DrawRectangle(GetScreenWidth()/2 - 220, 350, 440, 50, LIGHTGRAY);
                DrawRectangleLines(GetScreenWidth()/2 - 220, 350, 440, 50, DARKGRAY);
                DrawText(name, GetScreenWidth()/2 - 210, 360, 40, MAROON);
                if ((int)(GetTime()*2.0f) % 2 == 0) DrawText("_", GetScreenWidth()/2 - 210 + MeasureText(name, 40), 360, 40, MAROON);
            }
            else
            {
                DrawText("RANKING ATUAL", (GetScreenWidth() - MeasureText("RANKING ATUAL", 30)) / 2, 220, 30, GOLD);
                const TIPO_SCORE* scores = GetHighScores();
                for (int i = 0; i < 5; i++)
                {
                    DrawText(TextFormat("%d. %-20s %d", i + 1, scores[i].nome, scores[i].score), 350, 280 + i * 40, 20, WHITE);
                }

                for (int i = 0; i < 2; i++)
                {
                    Color color = (i == currentOption) ? YELLOW : WHITE;
                    DrawText(options[i], (GetScreenWidth() - MeasureText(options[i], 40)) / 2, 550 + i * 50, 40, color);
                }
            }
            
        EndDrawing();
    }
    return 0;
}