#include "gameplay_screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Definições, Estruturas e Variáveis que pertencem APENAS à tela de jogo
#define MAP_COLS 24
#define MAP_ROWS 16
#define TILE_SIZE 50
#define STATUS_BAR_HEIGHT 60
#define MAX_MONSTERS 10
#define PLAYER_INVINCIBILITY_DURATION 1.5f

// ESTRUTURA PLAYER ATUALIZADA
typedef struct {
    Vector2 gridPos;
    int orientation;
    int lives;
    int score;
    bool isInvincible;
    float invincibilityTimer;
} Player;

typedef struct {
    Vector2 gridPos;
    int orientation;
    bool active;
} Monster;

// Variáveis estáticas do módulo
static Player player = { 0 };
static Monster monsters[MAX_MONSTERS] = { 0 };
static int monsterCount = 0;
static char map[MAP_ROWS][MAP_COLS] = { 0 };

static struct {
    Texture2D link_front, link_back, link_left, link_right;
    Texture2D enemy_front, enemy_back, enemy_left, enemy_right;
    Texture2D ground, obstacle;
} textures;


// Funções auxiliares (privadas a este módulo)
static void LoadMapFromFile(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        TraceLog(LOG_ERROR, "Não foi possível abrir o arquivo de mapa: %s", fileName);
        return;
    }
    monsterCount = 0;
    for (int r = 0; r < MAP_ROWS; r++) {
        for (int c = 0; c < MAP_COLS; c++) {
            char tile = fgetc(file);
            while (tile == '\n' || tile == '\r') tile = fgetc(file);
            map[r][c] = tile;
            if (tile == 'J') player.gridPos = (Vector2){ (float)c, (float)r };
            else if (tile == 'M' && monsterCount < MAX_MONSTERS) {
                monsters[monsterCount].gridPos = (Vector2){ (float)c, (float)r };
                monsters[monsterCount].active = true;
                monsters[monsterCount].orientation = 0;
                monsterCount++;
            }
        }
    }
    fclose(file);
}

static void InitGame(void) {
    textures.link_front = LoadTexture("resources/Link_front.png");
    textures.link_back = LoadTexture("resources/Link_back.png");
    textures.link_left = LoadTexture("resources/Link_left.png");
    textures.link_right = LoadTexture("resources/Link_right.png");
    textures.enemy_front = LoadTexture("resources/Enemy_front.png");
    textures.enemy_back = LoadTexture("resources/Enemy_back.png");
    textures.enemy_left = LoadTexture("resources/Enemy_left.png");
    textures.enemy_right = LoadTexture("resources/Enemy_right.png");
    textures.ground = LoadTexture("resources/Ground.png");
    textures.obstacle = LoadTexture("resources/Obstacle.png");
    
    LoadMapFromFile("nivel1.txt");
    player.lives = 3;
    player.score = 0;
    player.orientation = 0;
    
    player.isInvincible = false;
    player.invincibilityTimer = 0;
    
    srand(time(NULL));
}

static void UnloadGame(void) {
    UnloadTexture(textures.link_front);
    UnloadTexture(textures.link_back);
    UnloadTexture(textures.link_left);
    UnloadTexture(textures.link_right);
    UnloadTexture(textures.enemy_front);
    UnloadTexture(textures.enemy_back);
    UnloadTexture(textures.enemy_left);
    UnloadTexture(textures.enemy_right);
    UnloadTexture(textures.ground);
    UnloadTexture(textures.obstacle);
}

// Implementação da função pública da tela de jogo
int RunGameplayScreen(void)
{
    InitGame();

    float monsterMoveTimer = 0.0f;
    int activeMonsters = monsterCount;

    while (!WindowShouldClose())
    {
        // ATUALIZAÇÃO
        Vector2 oldPlayerPos = player.gridPos;

        if (player.isInvincible)
        {
            player.invincibilityTimer -= GetFrameTime();
            if (player.invincibilityTimer <= 0)
            {
                player.isInvincible = false;
            }
        }

        if (IsKeyPressed(KEY_D)) {
            player.orientation = 3; // Direita
            if (player.gridPos.x + 1 < MAP_COLS && map[(int)player.gridPos.y][(int)player.gridPos.x + 1] != 'P') player.gridPos.x++;
        } else if (IsKeyPressed(KEY_A)) {
            player.orientation = 2; // Esquerda
            if (player.gridPos.x - 1 >= 0 && map[(int)player.gridPos.y][(int)player.gridPos.x - 1] != 'P') player.gridPos.x--;
        } else if (IsKeyPressed(KEY_S)) {
            player.orientation = 0; // Baixo
            if (player.gridPos.y + 1 < MAP_ROWS && map[(int)player.gridPos.y + 1][(int)player.gridPos.x] != 'P') player.gridPos.y++;
        } else if (IsKeyPressed(KEY_W)) {
            player.orientation = 1; // Cima
            if (player.gridPos.y - 1 >= 0 && map[(int)player.gridPos.y - 1][(int)player.gridPos.x] != 'P') player.gridPos.y--;
        }

        monsterMoveTimer += GetFrameTime();
        if (monsterMoveTimer >= 0.8f) {
            monsterMoveTimer = 0.0f;
            for (int i = 0; i < monsterCount; i++) {
                if (monsters[i].active) {
                    int move = rand() % 4;
                    Vector2 targetPos = monsters[i].gridPos;
                    if (move == 3 && targetPos.x + 1 < MAP_COLS && map[(int)targetPos.y][(int)targetPos.x + 1] != 'P') targetPos.x++;
                    else if (move == 2 && targetPos.x - 1 >= 0 && map[(int)targetPos.y][(int)targetPos.x - 1] != 'P') targetPos.x--;
                    else if (move == 0 && targetPos.y + 1 < MAP_ROWS && map[(int)targetPos.y + 1][(int)targetPos.x] != 'P') targetPos.y++;
                    else if (move == 1 && targetPos.y - 1 >= 0 && map[(int)targetPos.y - 1][(int)targetPos.x] != 'P') targetPos.y--;
                    monsters[i].gridPos = targetPos;
                    monsters[i].orientation = move;
                }
            }
        }
        
        if (!player.isInvincible)
        {
            for (int i = 0; i < monsterCount; i++)
            {
                if (monsters[i].active && player.gridPos.x == monsters[i].gridPos.x && player.gridPos.y == monsters[i].gridPos.y)
                {
                    player.lives--;
                    player.isInvincible = true;
                    player.invincibilityTimer = PLAYER_INVINCIBILITY_DURATION;
                    player.gridPos = oldPlayerPos; 
                    
                    switch(player.orientation)
                    {
                        case 0: player.orientation = 1; break;
                        case 1: player.orientation = 0; break;
                        case 2: player.orientation = 3; break;
                        case 3: player.orientation = 2; break;
                    }
                }
            }
        }
        
        if (IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < monsterCount; i++) {
                if (monsters[i].active) {
                    bool monsterHit = false;
                    for (int step = 1; step <= 3; step++) {
                        if (player.orientation == 3 && monsters[i].gridPos.x == player.gridPos.x + step && monsters[i].gridPos.y == player.gridPos.y) monsterHit = true;
                        // ---- LINHA CORRIGIDA ----
                        if (player.orientation == 2 && monsters[i].gridPos.x == player.gridPos.x - step && monsters[i].gridPos.y == player.gridPos.y) monsterHit = true;
                        if (player.orientation == 0 && monsters[i].gridPos.y == player.gridPos.y + step && monsters[i].gridPos.x == player.gridPos.x) monsterHit = true;
                        if (player.orientation == 1 && monsters[i].gridPos.y == player.gridPos.y - step && monsters[i].gridPos.x == player.gridPos.x) monsterHit = true;
                    }
                    if (monsterHit) {
                        monsters[i].active = false;
                        player.score += 100;
                        activeMonsters--;
                    }
                }
            }
        }
        
        if (player.lives <= 0) { UnloadGame(); return 0; }
        if (activeMonsters <= 0) { UnloadGame(); return 1; }

        // DESENHO
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(0, 0, GetScreenWidth(), STATUS_BAR_HEIGHT, DARKGRAY);
            DrawText(TextFormat("VIDAS: %d", player.lives), 20, 15, 30, WHITE);
            DrawText("NIVEL: 1", GetScreenWidth() / 2 - 50, 15, 30, WHITE);
            DrawText(TextFormat("SCORE: %d", player.score), GetScreenWidth() - 200, 15, 30, WHITE);

            for (int r = 0; r < MAP_ROWS; r++) {
                for (int c = 0; c < MAP_COLS; c++) {
                    Vector2 tilePos = { (float)c * TILE_SIZE, (float)r * TILE_SIZE + STATUS_BAR_HEIGHT };
                    if (map[r][c] == 'B' || map[r][c] == 'J' || map[r][c] == 'M') DrawTextureV(textures.ground, tilePos, WHITE);
                    else if (map[r][c] == 'P') DrawTextureV(textures.obstacle, tilePos, WHITE);
                }
            }

            for (int i = 0; i < monsterCount; i++) {
                if (monsters[i].active) {
                    Texture2D monsterTex;
                    if(monsters[i].orientation == 0) monsterTex = textures.enemy_front;
                    else if(monsters[i].orientation == 1) monsterTex = textures.enemy_back;
                    else if(monsters[i].orientation == 2) monsterTex = textures.enemy_left;
                    else monsterTex = textures.enemy_right;
                    DrawTextureV(monsterTex, (Vector2){ monsters[i].gridPos.x * TILE_SIZE, monsters[i].gridPos.y * TILE_SIZE + STATUS_BAR_HEIGHT }, WHITE);
                }
            }
            
            Texture2D playerTex;
            if(player.orientation == 0) playerTex = textures.link_front;
            else if(player.orientation == 1) playerTex = textures.link_back;
            else if(player.orientation == 2) playerTex = textures.link_left;
            else playerTex = textures.link_right;

            Vector2 playerPixelPos = { player.gridPos.x * TILE_SIZE, player.gridPos.y * TILE_SIZE + STATUS_BAR_HEIGHT };
            
            if (player.isInvincible)
            {
                if ((int)(player.invincibilityTimer * 10) % 2 != 0)
                {
                    DrawTextureV(playerTex, playerPixelPos, WHITE);
                }
            }
            else
            {
                DrawTextureV(playerTex, playerPixelPos, WHITE);
            }

        EndDrawing();
    }
    
    UnloadGame();
    return -1;
}