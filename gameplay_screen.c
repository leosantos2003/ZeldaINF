#include "gameplay_screen.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include "combat.h"
#include "ui.h"
#include "renderer.h"
#include "stdio.h"
#include "raylib.h"

int RunGameplayScreen(int level)
{
    char fileName[20];
    sprintf(fileName, "nivel%d.txt", level);
    LoadLevel(fileName); 
    
    Player *player = GetPlayer();
    Monster *monsters = GetMonsters();
    
    while (!WindowShouldClose())
    {
        Vector2 oldPlayerPos = player->gridPos;
        UpdatePlayer(GetMap());
        UpdateMonsters(GetMap(), level);
        ProcessPlayerAttack(player, monsters, level);
        ProcessCollisions(player, monsters, oldPlayerPos);
        
        if (IsPlayerDead() || !AreAnyMonstersLeft()) {
             return player->score;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawGameLevel();
            DrawGameMonsters(monsters);
            DrawGamePlayer(player);
            
            int attackOrientation, attackRange;
            if (IsPlayerAttacking(&attackOrientation, &attackRange))
            {
                DrawGameAttack(player, attackOrientation, attackRange);
            }
            
            DrawGameplayUI(player, level);
            
        EndDrawing();
    }
    
    return -1;
}