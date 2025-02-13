#ifndef SAMURAI_H
#define SAMURAI_H

#include <stddef.h>
#include "raylib.h"
#include "fire.h"
#include "platform.h"
#include "portal.h"

typedef struct SamuraiAssets {
    Texture2D idleTexture;
    Texture2D runTexture;
    Texture2D attackTexture;
    Texture2D hurtTexture;
} SamuraiAssets;

typedef struct SamuraiAnimation {
    int frameIndex;
    float frameCounter;
    int attackFrame;
    SamuraiAssets assets;
} SamuraiAnimation;

typedef struct SamuraiStats {
    int hitpoints;
    int damage;
    float jumpStrength;
    float gravityEffect;
} SamuraiStats;

typedef struct SamuraiState {
    bool facingLeft;
    bool isRunning;
    bool isJumping;
    bool isAttacking;
    bool isHurt;
    bool isDead;
    bool isImmune;
} SamuraiState;

typedef struct SamuraiSlash {
    Vector2 position;
    float width;
    float height;
    int damage;
    bool isActive;
} SamuraiSlash;

typedef struct Samurai {
    Vector2 position;
    Vector2 speed;
    SamuraiStats stats;
    SamuraiState state;
    SamuraiAnimation animation;
    SamuraiSlash slash;
} Samurai;

void updateSamuraiAnimation(Samurai *samurai);
void updateSamuraiMovement(Samurai *samurai);
void updateSamuraiPhysics(Samurai *samurai, Platforms *platforms, Fires *fires);
void updateSamurai(Samurai *samurai, Platforms *platforms, Fires *fires);
void renderSamurai(Samurai *samurai);
bool samuraiPassesPortal(Samurai *samurai, Portal *portal);

#endif // SAMURAI_H
