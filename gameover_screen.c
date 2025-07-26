#include "gameover_screen.h"
#include "raylib.h"

int RunGameOverScreen(void)
{
    // Opções disponíveis nesta tela
    const char *options[] = {
        "Reiniciar",
        "Sair"
    };
    const int optionsCount = sizeof(options) / sizeof(options[0]);
    int currentOption = 0;

    // Loop da tela de Fim de Jogo
    while (!WindowShouldClose())
    {
        // ATUALIZAÇÃO - Lógica de navegação do menu
        if (IsKeyPressed(KEY_DOWN))
        {
            currentOption++;
            if (currentOption >= optionsCount) currentOption = 0;
        }
        else if (IsKeyPressed(KEY_UP))
        {
            currentOption--;
            if (currentOption < 0) currentOption = optionsCount - 1;
        }

        // Verifica a seleção com a tecla ENTER
        if (IsKeyPressed(KEY_ENTER))
        {
            switch (currentOption)
            {
                case 0: return 1; // "Jogar novamente"
                case 1: return 0; // "Sair"
            }
        }

        // DESENHO
        BeginDrawing();
            ClearBackground(BLACK);

            // Mensagem principal
            const char *message = "Você morreu!";
            int msgFontSize = 120;
            int msgWidth = MeasureText(message, msgFontSize);
            DrawText(message, (GetScreenWidth() - msgWidth) / 2, GetScreenHeight() / 4, msgFontSize, RED);

            // Opções
            int initialY = GetScreenHeight() / 2; //+50?
            int spacing = 60;
            int fontSize = 50;

            for (int i = 0; i < optionsCount; i++)
            {
                Color textColor = (i == currentOption) ? YELLOW : WHITE;
                int textWidth = MeasureText(options[i], fontSize);
                int posX = (GetScreenWidth() - textWidth) / 2;
                int posY = initialY + i * spacing;
                DrawText(options[i], posX, posY, fontSize, textColor);

                if (i == currentOption)
                {
                    DrawText("-", posX - 50, posY, fontSize, RED);
                }
            }

        EndDrawing();
    }

    return 0; // Se sair pela janela, considera como "Sair"
}