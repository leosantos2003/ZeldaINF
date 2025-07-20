#include "ui.h"
#include "raylib.h"

void DrawGameplayUI(const Player *player, int level)
{
    DrawRectangle(0, 0, GetScreenWidth(), 60, DARKGRAY);
    DrawText(TextFormat("VIDAS: %d", player->lives), 20, 15, 30, WHITE);
    DrawText(TextFormat("NIVEL: %d", level), GetScreenWidth() / 2 - 50, 15, 30, WHITE);
    DrawText(TextFormat("SCORE: %d", player->score), GetScreenWidth() - 200, 15, 30, WHITE);
}