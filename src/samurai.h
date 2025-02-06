#ifndef SAMURAI_H
#define SAMURAI_H

#include <stddef.h>

#include "raylib.h"

typedef struct Samurai {
    Vector2 position;
    float xSpeed;
    float ySpeed;
    float jumpStrength;
    float gravityEffect;
    Texture2D idleTexture;
    Texture2D runTexture;
    Texture2D attackTexture;
    int frameIndex;
    float frameCounter;
    bool facingRight;
    bool isRunning;
    bool isJumping;
    bool isAttacking;
} Samurai;

void updateSamurai(Samurai *samurai);
void renderSamurai(Samurai *samurai);

#endif // SAMURAI_H
