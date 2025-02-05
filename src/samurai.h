#ifndef SAMURAI_H
#define SAMURAI_H

#include <stddef.h>

#include "raylib.h"

typedef struct Samurai {
    Vector2 position;
    float xSpeed;
    float ySpeed;
    bool isJumping;
    float jumpStrength;
    float gravityEffect;
    Texture2D idleTexture;
    int frameIndex;
    bool facingRight;
    float frameCounter;
} Samurai;

void updateSamurai(Samurai *samurai);
void renderSamurai(Samurai *samurai);

#endif // SAMURAI_H
