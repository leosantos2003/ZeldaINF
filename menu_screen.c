#include "raylib.h"
#include "menu_screen.h"

// Implementação da função da tela de menu
int RunMenuScreen(void)
{
    const char *menuOptions[] = {
        "Iniciar",
        "Scoreboard",
        "Sair"
    };
    const int menuOptionsCount = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int currentOption = 0;
    
    while (!WindowShouldClose())
    {
        // ATUALIZAÇÃO
        if (IsKeyPressed(KEY_DOWN))
        {
            currentOption++;
            if (currentOption >= menuOptionsCount) currentOption = 0;
        }
        else if (IsKeyPressed(KEY_UP))
        {
            currentOption--;
            if (currentOption < 0) currentOption = menuOptionsCount - 1;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            switch (currentOption)
            {
                case 0: return 1; // Iniciar
                case 1: return 2; // Scoreboard
                case 2: return 0; // Sair
            }
        }

        // DESENHO
        BeginDrawing();
            ClearBackground(BLACK);

            const char *title = "ZINF";
            int titleFontSize = 160;
            int titleWidth = MeasureText(title, titleFontSize);
            DrawText(title, (GetScreenWidth() - titleWidth) / 2, GetScreenHeight() / 4 - 80, titleFontSize, WHITE);

            int initialY = GetScreenHeight() / 2;
            int spacing = 60;
            int fontSize = 50;

            for (int i = 0; i < menuOptionsCount; i++)
            {
                Color textColor = (i == currentOption) ? YELLOW : WHITE;
                int textWidth = MeasureText(menuOptions[i], fontSize);
                int posX = (GetScreenWidth() - textWidth) / 2;
                int posY = initialY + i * spacing;

                DrawText(menuOptions[i], posX, posY, fontSize, textColor);

                if (i == currentOption)
                {
                    DrawText("-", posX - 50, posY, fontSize, RED);
                }
            }
        EndDrawing();
    }
    
    return 0; // Sair pela janela
}