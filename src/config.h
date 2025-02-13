#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG_RAYLIB true

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define FPS 60

#define SAMURAI_FRAME_SIZE 200
#define SAMURAI_ANIMATION_SPEED 12

#define SAMURAI_RUN_TEXTURE "samurai_run.png"
#define SAMURAI_RUN_FRAME_COUNT 16

#define SAMURAI_IDLE_TEXTURE "samurai_idle.png"
#define SAMURAI_IDLE_FRAME_COUNT 10

#define SAMURAI_ATTACK_TEXTURE "samurai_attack.png"
#define SAMURAI_ATTACK_FRAME_COUNT 7

#define SAMURAI_SLASH_FRAME 5
#define SAMURAI_ATTACK_RANGE 75

#define SAMURAI_HURT_TEXTURE "samurai_hurt.png"
#define SAMURAI_HURT_FRAME_COUNT 4
#define SAMURAI_MAX_HITPOINTS 100.0

#define SAMURAI_X_MOD 0.40 * SAMURAI_FRAME_SIZE // 80
#define SAMURAI_X_REC 0.20 * SAMURAI_FRAME_SIZE // 40
#define SAMURAI_Y_MOD 0.48 * SAMURAI_FRAME_SIZE // 96
#define SAMURAI_Y_REC 0.36 * SAMURAI_FRAME_SIZE // 72

#define SAMURAI_X_SLIM_MOD 0.45 * SAMURAI_FRAME_SIZE // 90
#define SAMURAI_X_SLIM_REC 0.10 * SAMURAI_FRAME_SIZE // 20
#define SAMURAI_Y_SLIM_MOD 0.82 * SAMURAI_FRAME_SIZE // 166
#define SAMURAI_Y_SLIM_REC 0.04 * SAMURAI_FRAME_SIZE // 8

#define MAX_LEVEL 1

#define MAX_PLATFORMS 10

#define MAX_FIRES 255

#define MAX_NPCS 127

#endif // CONFIG_H
