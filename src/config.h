#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define FPS 60
#define DEBUG_RAYLIB true

#define SAMURAI_FRAME_SIZE 200
#define SAMURAI_ANIMATION_SPEED 10
#define SAMURAI_RUN_TEXTURE "samurai_run.png"
#define SAMURAI_RUN_FRAME_COUNT 16
#define SAMURAI_IDLE_TEXTURE "samurai_idle.png"
#define SAMURAI_IDLE_FRAME_COUNT 10
#define SAMURAI_ATTACK_TEXTURE "samurai_attack.png"
#define SAMURAI_ATTACK_FRAME_COUNT 7
#define SAMURAI_HURT_TEXTURE "samurai_hurt.png"
#define SAMURAI_HURT_FRAME_COUNT 4
//#define SAMURAI_X_MOD 7.8 * SAMURAI_FRAME_SIZE / 23
//#define SAMURAI_Y_MOD 10.5 * SAMURAI_FRAME_SIZE / 23
//#define SAMURAI_X_REC 7.5 * SAMURAI_FRAME_SIZE / 23
//#define SAMURAI_Y_REC 9.5 * SAMURAI_FRAME_SIZE / 23
#define SAMURAI_X_MOD 0.398 * SAMURAI_FRAME_SIZE  // Adjust based on visual alignment
#define SAMURAI_Y_MOD 0.48 * SAMURAI_FRAME_SIZE  // Adjust based on visual alignment
#define SAMURAI_X_REC 0.20 * SAMURAI_FRAME_SIZE  // Width of the collision rectangle
#define SAMURAI_Y_REC 0.36 * SAMURAI_FRAME_SIZE  // Height of the collision rectangle
//
#define MAX_PLATFORMS 10

#endif // CONFIG_H
