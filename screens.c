// Inclui o cabeçalho do próprio módulo, que por sua vez já inclui raylib.h
#include "screens.h" 

// A função RunMenuScreen é responsável por toda a lógica e desenho da tela de menu.
// Ela retorna um inteiro que representa a escolha do usuário.
int RunMenuScreen(void)
{
    // ---- INICIALIZAÇÃO DAS VARIÁVEIS ESPECÍFICAS DO MENU ----

    // Array com o texto de cada opção do menu. 
    // Deixar os colchetes vazios [] faz o compilador contar o número de itens.
    const char *menuOptions[] = {
        "Iniciar",
        "Scoreboard",
        "Sair"
    };
    
    // Calcula o número de itens no array de opções.
    // Esta é a forma segura e flexível de fazer isso em C.
    const int menuOptionsCount = sizeof(menuOptions) / sizeof(menuOptions[0]);
    
    // Variável para armazenar o índice da opção atualmente selecionada. Começa com '0' (Iniciar).
    int currentOption = 0;
    
    // ---- LOOP PRINCIPAL DA TELA DE MENU ----
    // Este loop continuará rodando enquanto o usuário não fechar a janela pelo botão 'X'.
    while (!WindowShouldClose())
    {
        // ---- SEÇÃO DE ATUALIZAÇÃO (Processamento de Entradas) ----

        // Verifica se a tecla SETA PARA BAIXO foi pressionada
        if (IsKeyPressed(KEY_DOWN))
        {
            currentOption++; // Move a seleção para a próxima opção
            // Se passar da última opção, volta para a primeira
            if (currentOption >= menuOptionsCount) currentOption = 0;
        }
        // Verifica se a tecla SETA PARA CIMA foi pressionada
        else if (IsKeyPressed(KEY_UP))
        {
            currentOption--; // Move a seleção para a opção anterior
            // Se passar da primeira opção (indo para cima), vai para a última
            if (currentOption < 0) currentOption = menuOptionsCount - 1;
        }

        // Verifica se a tecla ENTER foi pressionada
        if (IsKeyPressed(KEY_ENTER))
        {
            // Executa uma ação com base na opção que estava selecionada
            switch (currentOption)
            {
                case 0: return 1; // "Iniciar": para a função e retorna 1 para o main.c
                case 1: return 2; // "Scoreboard": para a função e retorna 2 para o main.c
                case 2: return 0; // "Sair": para a função e retorna 0 para o main.c
            }
        }

        // ---- SEÇÃO DE DESENHO (Renderização na Tela) ----
        BeginDrawing(); // Prepara a tela para o desenho

            // Limpa toda a tela com a cor preta para não deixar rastros do quadro anterior
            ClearBackground(BLACK);

            // ---- Desenha o Título do Jogo ----
            const char *title = "ZINF";
            int titleFontSize = 160;
            // Mede o tamanho do texto para poder centralizá-lo
            int titleWidth = MeasureText(title, titleFontSize);
            // Desenha o texto na tela
            DrawText(title, (GetScreenWidth() - titleWidth) / 2, GetScreenHeight() / 4 - 80, titleFontSize, WHITE);

            // ---- Desenha as Opções do Menu ----
            int initialY = GetScreenHeight() / 2; // Posição Y inicial para a primeira opção
            int spacing = 60;   // Espaçamento vertical entre as opções
            int fontSize = 50;  // Tamanho da fonte para as opções

            // Loop que passa por cada opção do menu para desenhá-la
            for (int i = 0; i < menuOptionsCount; i++)
            {
                // Operador Ternário: um if/else em uma linha.
                // Se (i == currentOption) for verdadeiro, a cor é AMARELO, senão, é BRANCO.
                Color textColor = (i == currentOption) ? YELLOW : WHITE;
                
                // Mede o texto da opção atual para centralizá-lo
                int textWidth = MeasureText(menuOptions[i], fontSize);
                int posX = (GetScreenWidth() - textWidth) / 2;
                int posY = initialY + i * spacing;

                // Desenha o texto da opção
                DrawText(menuOptions[i], posX, posY, fontSize, textColor);

                // Se esta for a opção selecionada, desenha um traço vermelho ao lado
                if (i == currentOption)
                {
                    DrawText("-", posX - 50, posY, fontSize, RED);
                }
            }
            
        EndDrawing(); // Finaliza o desenho do quadro atual
    }
    
    // Se o loop terminar porque o usuário clicou no 'X' da janela, 
    // retorna 0, que no nosso main.c também significa "Sair".
    return 0; 
}