#ifndef NPC_H
#define NPC_H

#include "stddef.h"
//#include "string.h"

#include "raylib.h"

#include "config.h"

struct SamuraiAssets;
struct SamuraiAnimation;
struct SamuraiStats;
struct SamuraiState;
struct SamuraiSlash;
struct SamuraiHitbox;
struct Samurai;

typedef struct NPCAssets {
    Texture2D idleTexture;
    Texture2D attackTexture;
    Texture2D hurtTexture;
    Texture2D deathTexture;
    Texture2D flyingTexture;
    Texture2D projectileTexture;
} NPCAssets;

typedef struct NPCAnimation {
    int frameIndex;
    float frameCounter;
    float attackFrame;
    NPCAssets assets;
} NPCAnimation;

typedef struct NPCState {
    bool isIdle;
    bool isFlying;  
    bool isAttacking;
    bool isHurt;
    bool isDead;
    bool facingLeft;
} NPCState;

typedef struct NPCProjectile {
    Vector2 position;
    Vector2 speed;
    int damage;
} NPCProjectile;

typedef struct NPCProjectiles {
    NPCProjectile units[MAX_NPC_PROJECTILES];
    int count;
} NPCProjectiles;

typedef struct NPC {
    Rectangle rect;
    Color color;
    float hitpoints;
    float damage;
    float attackCooldown;
    float attackCooldownRemaining;
    NPCAnimation animation;
    NPCState state;
    Vector2 position;
    Vector2 speed;
    NPCProjectiles projectiles;
} NPC;


typedef struct NPCS {
    NPC units[MAX_NPCS];
    int count;
} NPCS;

void updateNPCAnimation(NPC *npc, float *deltaTime);
void removeNPC(NPCS *npcs, int n);
void updateNPC(NPC *npc, struct Samurai *samurai, float *deltaTime);
void updateNPCS(NPCS *npcs, struct Samurai *samurai, float *deltaTime);
void newNPC(NPCS *npcs, NPCAssets loadedAssets, Vector2 *position, int width, int height, Color color,
            float hitpoints, float damage, float attackCooldown);
void resetNPCS(NPCS *npcs);

void npcsLevel0(NPCS *npcs, NPCAssets NPCLoadedAssets);
void npcsLevel1(NPCS *npcs, NPCAssets NPCLoadedAssets);

#endif // NPC_H
