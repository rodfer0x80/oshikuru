#ifndef SAMURAI_H
#define SAMURAI_H

#include <stddef.h>

#include "raylib.h"

typedef struct Samurai {
    Vector2 position;
    float xSpeed;
    float ySpeed;
    int hitpoints;
    float jumpStrength;
    float gravityEffect;
    Texture2D idleTexture;
    Texture2D runTexture;
    Texture2D attackTexture;
    Texture2D hurtTexture;
    int frameIndex;
    float frameCounter;
    bool facingLeft;
    bool isRunning;
    bool isJumping;
    bool isAttacking;
    bool isHurt;
    bool isDead;
} Samurai;

void updateSamurai(Samurai *samurai);

void renderSamurai(Samurai *samurai);

bool samuraiPassesPortal(Samurai *samurai);

#endif // SAMURAI_H
