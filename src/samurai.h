#ifndef SAMURAI_H
#define SAMURAI_H

#include <stddef.h>

#include "raylib.h"
#include "platform.h"
#include "portal.h"

typedef struct Slash {
    Vector2 position;
    int width;
    int height;
    int damage;
    bool isActive;
} Slash;

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
    int damage;
    int attackTimer;
    Slash slash;
} Samurai;

void updateSamuraiAnimation(Samurai *samurai);
void updateSamuraiMovement(Samurai *samurai);
void updateSamuraiPhysics(Samurai *samurai, Platforms *platforms);
void updateSamurai(Samurai *samurai, Platforms *platforms);
void renderSamurai(Samurai *samurai);
bool samuraiPassesPortal(Samurai *samurai, Portal *portal);

#endif // SAMURAI_H
