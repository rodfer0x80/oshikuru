#ifndef CONFIG_H
#define CONFIG_H

// DEBUG
#define DEBUG_RAYLIB true

// MAIN
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FPS 60

// SAMURAI
#define SAMURAI_FRAME_SIZE 200
#define SAMURAI_ANIMATION_SPEED 12
#define SAMURAI_RUN_TEXTURE "entities/samurai/run.png"
#define SAMURAI_RUN_FRAME_COUNT 16
#define SAMURAI_IDLE_TEXTURE "entities/samurai/idle.png"
#define SAMURAI_IDLE_FRAME_COUNT 10
#define SAMURAI_ATTACK_TEXTURE "entities/samurai/attack.png"
#define SAMURAI_ATTACK_FRAME_COUNT 7
#define SAMURAI_SLASH_FRAME 5
#define SAMURAI_SLASH_FRAME_COUNT 10 // 2 * SAMURAI_SLASH_FRAME
#define SAMURAI_ATTACK_RANGE 75
#define SAMURAI_HURT_TEXTURE "entities/samurai/hurt.png"
#define SAMURAI_HURT_FRAME_COUNT 4
#define SAMURAI_MAX_HITPOINTS 100.0f
#define SAMURAI_X_MOD 0.40 * SAMURAI_FRAME_SIZE      // 80
#define SAMURAI_X_REC 0.20 * SAMURAI_FRAME_SIZE      // 40
#define SAMURAI_Y_MOD 0.48 * SAMURAI_FRAME_SIZE      // 96
#define SAMURAI_Y_REC 0.36 * SAMURAI_FRAME_SIZE      // 72
#define SAMURAI_X_SLIM_MOD 0.45 * SAMURAI_FRAME_SIZE // 90
#define SAMURAI_X_SLIM_REC 0.10 * SAMURAI_FRAME_SIZE // 20
#define SAMURAI_Y_SLIM_MOD 0.82 * SAMURAI_FRAME_SIZE // 166
#define SAMURAI_Y_SLIM_REC 0.04 * SAMURAI_FRAME_SIZE // 8

// NPC
#define NPC_FRAME_SIZE 200
#define NPC_ANIMATION_SPEED 8.0f
#define NPC_IDLE_FRAME_COUNT 4
#define NPC_FLYING_FRAME_COUNT 4  
#define NPC_ATTACK_FRAME_COUNT 8
#define NPC_HURT_FRAME_COUNT 4
#define NPC_DEATH_FRAME_COUNT 6
#define NPC_PROJECTILE_FRAME_COUNT 1
#define NPC_IDLE_TEXTURE "entities/demon/idle.png"
#define NPC_ATTACK_TEXTURE "entities/demon/attack.png"
#define NPC_HURT_TEXTURE "entities/demon/hurt.png"
#define NPC_DEATH_TEXTURE "entities/demon/death.png"
#define NPC_FLYING_TEXTURE "entities/demon/flying.png"
#define NPC_PROJECTILE_TEXTURE "entities/demon/projectile.png"

// LEVEL
#define MAX_LEVEL 1

// PLATFORM
#define MAX_PLATFORMS 10

// FIRE
#define MAX_FIRES 255

// NPC
#define MAX_NPCS 127
#define MAX_NPC_PROJECTILES 255

// PORTAL
#define PORTAL_TEXTURE "world/portal/portal.png"
#define PORTAL_FRAME_COUNT 6 
#define PORTAL_ANIMATION_SPEED 8 
#define PORTAL_FRAME_SIZE 200

#endif // CONFIG_H
