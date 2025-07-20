#include "combat.h"
#include "raylib.h" // Necessário para IsKeyPressed

// Variáveis estáticas para controlar o estado do ataque
static bool isAttacking = false;
static float attackTimer = 0.0f;
static int attackOrientation = 0;
static int currentAttackRange = 0;

void ProcessPlayerAttack(Player *player, Monster monsters[], int level)
{
    if (isAttacking)
    {
        attackTimer -= GetFrameTime();
        if (attackTimer <= 0) isAttacking = false;
    }

    if (IsKeyPressed(KEY_J) && !isAttacking)
    {
        isAttacking = true;
        attackTimer = 0.3f; // ATTACK_DURATION
        attackOrientation = player->orientation;

        currentAttackRange = 3;
        if (level == 3) currentAttackRange = 2;

        for (int step = 1; step <= currentAttackRange; step++)
        {
            Vector2 targetPos = player->gridPos;
            if(attackOrientation == 0) targetPos.y += step;
            else if(attackOrientation == 1) targetPos.y -= step;
            else if(attackOrientation == 2) targetPos.x -= step;
            else if(attackOrientation == 3) targetPos.x += step;

            for (int i = 0; i < MAX_MONSTERS; i++)
            {
                if (monsters[i].active && !monsters[i].isDying && monsters[i].gridPos.x == targetPos.x && monsters[i].gridPos.y == targetPos.y)
                {
                    DamageMonster(i);
                    player->score += 100;
                }
            }
        }
    }
}

void ProcessCollisions(Player *player, Monster monsters[], Vector2 oldPlayerPos)
{
    if (player->isInvincible) return;

    for (int i = 0; i < MAX_MONSTERS; i++)
    {
        if (monsters[i].active && !monsters[i].isDying && player->gridPos.x == monsters[i].gridPos.x && player->gridPos.y == monsters[i].gridPos.y)
        {
            DamagePlayer(oldPlayerPos);
        }
    }
}

// Função para o gameplay_screen saber se deve desenhar o ataque
bool IsPlayerAttacking(int *orientation, int *range)
{
    if (isAttacking)
    {
        *orientation = attackOrientation;
        *range = currentAttackRange;
        return true;
    }
    return false;
}