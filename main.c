#include "raylib.h"
#include "menu_screen.h"
#include "gameplay_screen.h"
#include "player.h"
#include "renderer.h"
#include "scoreboard.h"
#include "endscreen.h"
#include "screens.h"

#include "enter_name_screen.h"

#define TOTAL_LEVELS 3

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 860;
    InitWindow(screenWidth, screenHeight, "ZINF - Zelda INF");
    
    InitRenderer();
    LoadHighScores();
    SetTargetFPS(60);

    int currentScreen = 0; 
    int currentLevel = 1;
    
    static int finalScore = 0;
    static int nextScreenAfterName = 0;

    while (currentScreen != -1 && !WindowShouldClose())
    {
        switch (currentScreen)
        {
            case 0:
            {
                int menuChoice = RunMenuScreen();

                if (menuChoice == 1) {
                    currentLevel = 1;
                    InitPlayerState(); 
                    currentScreen = 1; 
                } 
                else if (menuChoice == 0) {
                    currentScreen = -1;
                }
            } break;
            

            case 1:
            {
                finalScore = RunGameplayScreen(currentLevel);
                
                if (finalScore == -1) {
                    currentScreen = -1;
                    break;
                }

                bool playerDied = (GetPlayer()->lives <= 0);
                bool playerWonGame = (!playerDied && currentLevel >= TOTAL_LEVELS);

                if (playerDied || playerWonGame)
                {
                    if (IsHighScore(finalScore))
                    {
                        nextScreenAfterName = playerDied ? SCREEN_GAMEOVER : SCREEN_WIN;
                        currentScreen = 4;
                    }
                    else
                    {
                        currentScreen = playerDied ? SCREEN_GAMEOVER : SCREEN_WIN;
                    }
                }
                else
                {
                    currentLevel++;
                    currentScreen = SCREEN_GAMEPLAY;
                }
            } break;

            case 2:
            {
               GameScreen choice = RunEndScreen(false, finalScore);
                if (choice == SCREEN_GAMEPLAY) { 
                    currentLevel = 1;
                    InitPlayerState();
                    currentScreen = SCREEN_GAMEPLAY;
                } else { 
                    currentScreen = -1;
                }
            } break;

            case 3:
            {
               GameScreen choice = RunEndScreen(true, finalScore);
                if (choice == SCREEN_GAMEPLAY) { 
                    currentLevel = 1;
                    InitPlayerState(); 
                    currentScreen = SCREEN_GAMEPLAY;
                } else { 
                    currentScreen = -1;
                }
            } break;

            case 4:
            {
                RunEnterNameScreen(finalScore);
                currentScreen = nextScreenAfterName;
            } break;
        }
    }

    UnloadRenderer();
    CloseWindow();
    
    return 0;
}