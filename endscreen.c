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
    const char *titleText = didWin ? "Você venceu!" : "Você morreu...";
    Color titleColor = didWin ? GREEN : RED;

    const char *options[] = { "Jogar novamente", "Sair" };
    int currentOption = 0;

    int frameCounter = 0;

    while (!WindowShouldClose())
    {
        if (frameCounter > 5)
        {
            if (IsKeyPressed(KEY_DOWN)) currentOption = (currentOption + 1) % 2;
            if (IsKeyPressed(KEY_UP)) currentOption = (currentOption - 1 + 2) % 2;
            
            if (IsKeyPressed(KEY_ENTER))
            {
                if (currentOption == 0) return SCREEN_GAMEPLAY;
                if (currentOption == 1) return SCREEN_MENU;
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawText(titleText, (GetScreenWidth() - MeasureText(titleText, 100)) / 2, 80, 100, titleColor);

            DrawText("Ranking atual", (GetScreenWidth() - MeasureText("Ranking atual", 30)) / 2, 220, 30, GOLD);
            const TIPO_SCORE* scores = GetHighScores();
            
            const int scoreboardWidth = 500;
            const int startX = (GetScreenWidth() - scoreboardWidth) / 2;
            const int endX = startX + scoreboardWidth;

            for (int i = 0; i < 5; i++)
            {
                DrawText(TextFormat("%d. %.19s", i + 1, scores[i].nome), startX, 280 + i * 40, 20, WHITE);

                const char* rightText = TextFormat("%d", scores[i].score);
                int rightTextWidth = MeasureText(rightText, 20);
                DrawText(rightText, endX - rightTextWidth, 280 + i * 40, 20, GOLD);
            }
            
            for (int i = 0; i < 2; i++)
            {
                Color color = (i == currentOption) ? YELLOW : WHITE;
                int fontSize = 40;
                const char* text = options[i];
                int textWidth = MeasureText(text, fontSize);
                int posX = (GetScreenWidth() - textWidth) / 2;
                int posY = 550 + i * 50;

                DrawText(text, posX, posY, fontSize, color);

                if (i == currentOption)
                {
                    DrawText("-", posX - 50, posY, fontSize, RED);
                }
            }
            
        EndDrawing();

        frameCounter++;
    }
    
    return SCREEN_MENU;
}