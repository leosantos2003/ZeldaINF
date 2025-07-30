#include "enter_name_screen.h"
#include "scoreboard.h"
#include "raylib.h"

void RunEnterNameScreen(int score)
{
    char name[20] = { '\0' };
    int letterCount = 0;
    // A variável 'nameSubmitted' não é mais necessária.

    while (!WindowShouldClose())
    {
        // --- ATUALIZAÇÃO ---
        // A lógica de atualização agora só precisa lidar com a entrada do nome.
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
        if (IsKeyPressed(KEY_ENTER) && letterCount > 0)
        {
            AddHighScore(score, name);
            SaveHighScores();
            return; // <- ALTERAÇÃO PRINCIPAL: Retorna imediatamente!
        }
        
        // --- DESENHO ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            // O código de desenho agora só precisa da parte de entrada de texto.
            DrawText("NOVO RECORDE!", (GetScreenWidth() - MeasureText("NOVO RECORDE!", 60))/2, 150, 60, GOLD);
            DrawText("DIGITE SEU NOME:", (GetScreenWidth() - MeasureText("DIGITE SEU NOME:", 20))/2, 280, 20, LIGHTGRAY);
            
            DrawRectangle(GetScreenWidth()/2 - 220, 350, 440, 50, LIGHTGRAY);
            DrawRectangleLines(GetScreenWidth()/2 - 220, 350, 440, 50, DARKGRAY);
            DrawText(name, GetScreenWidth()/2 - 210, 360, 40, MAROON);
            
            // Desenha um cursor piscando
            if (((int)(GetTime()*2.0f) % 2) == 0)
            {
                DrawText("_", GetScreenWidth()/2 - 210 + MeasureText(name, 40), 360, 40, MAROON);
            }
            
        EndDrawing();
    }
}