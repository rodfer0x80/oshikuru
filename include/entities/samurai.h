#ifndef SAMURAI_H
#define SAMURAI_H

#include <stddef.h>

#include "raylib.h"

#include "config.h"
#include "world/fire.h"
#include "world/platform.h"
#include "world/portal.h"

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
    int lives;
    float hitpoints;
    float damage;
    float jumpStrength;
    float gravityEffect;
} SamuraiStats;

typedef struct SamuraiState {
    bool facingLeft; //TODO: isFacingLeft
    bool isRunning;
    bool isJumping;
    bool isAttacking;
    bool isHurt;
    bool isDead;
    bool hasDied;
    bool isImmune;
} SamuraiState;

typedef struct SamuraiSlash {
    Vector2 position;
    float width;
    float height;
    float damage;
    bool isActive;
} SamuraiSlash;

typedef struct SamuraiHitbox {
    Rectangle rec;
    Rectangle slimRec;
} SamuraiHitbox;

typedef struct Samurai {
    Vector2 position;
    Vector2 speed;
    SamuraiHitbox hitbox;
    SamuraiStats stats;
    SamuraiState state;
    SamuraiAnimation animation;
    SamuraiSlash slash;
} Samurai;

void samuraiHitFor(Samurai *samurai, float damage);

void updateSamuraiAnimation(Samurai *samurai, float *deltaTime);

void updateSamuraiMovement(Samurai *samurai);

void updateSamuraiPhysics(Samurai *samurai, Platforms *platforms, Fires *fires);

void updateSamurai(Samurai *samurai, Platforms *platforms, Fires *fires, float *deltaTime);

bool samuraiPassesPortal(Samurai *samurai, Portal *portal);

#endif // SAMURAI_H
