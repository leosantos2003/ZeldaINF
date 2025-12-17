#include "menu_screen.h"
#include "raylib.h"
#include "renderer.h"

int RunMenuScreen(void)
{
    const char *menuOptions[] = {
        "Jogar",
        "Sair"
    };
    const int menuOptionsCount = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int currentOption = 0;
    
    while (!WindowShouldClose())
    {
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
                case 0: return 1;
                case 1: return 0;
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);

            const char *title = "ZINF";
            int titleFontSize = 160;
            int titleWidth = MeasureText(title, titleFontSize);
            DrawText(title, (GetScreenWidth() - titleWidth) / 2, GetScreenHeight() / 4 - 80, titleFontSize, WHITE);

            int initialY = GetScreenHeight() / 2;
            int spacing = 60;
            int fontSize = 50;
            int offsetX = -200;

            for (int i = 0; i < menuOptionsCount; i++)
            {
                Color textColor = (i == currentOption) ? YELLOW : WHITE;
                int textWidth = MeasureText(menuOptions[i], fontSize);
                int posX = (GetScreenWidth() - textWidth) / 2 + offsetX;
                int posY = initialY + i * spacing;

                DrawText(menuOptions[i], posX, posY, fontSize, textColor);

                if (i == currentOption)
                {
                    DrawText("-", posX - 50, posY, fontSize, RED);
                }
            }

            DrawMenuCharacter(GetScreenWidth() / 2 + 100, initialY - 30);

        EndDrawing();
    }
    
    return 0;
}