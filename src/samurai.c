#include "raylib.h"

#include "config.h"
#include "samurai.h"

void updateSamurai(Samurai *samurai) {
    // Animation update
    samurai->frameCounter += GetFrameTime() * SAMURAI_ANIMATION_SPEED;
    if (samurai->frameCounter >= 1.0f) {
        samurai->frameIndex = (samurai->frameIndex + 1) % SAMURAI_FRAME_COUNT;
        samurai->frameCounter = 0.0f;
    }

    // Movement
    bool isMoving = false;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        samurai->position.x -= samurai->xSpeed;
        samurai->facingRight = false;
        isMoving = true;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        samurai->position.x += samurai->xSpeed;
        samurai->facingRight = true;
        isMoving = true;
    }

    // Jump
    if (IsKeyPressed(KEY_SPACE) && !samurai->isJumping) {
        samurai->ySpeed = samurai->jumpStrength;
        samurai->isJumping = true;
    }

    // Apply gravity
    samurai->ySpeed += samurai->gravityEffect;
    samurai->position.y += samurai->ySpeed;

    // Ground collision
    if (samurai->position.y >= SCREEN_HEIGHT / 2 - SAMURAI_FRAME_SIZE / 2) {
        samurai->position.y = SCREEN_HEIGHT / 2 - SAMURAI_FRAME_SIZE / 2;
        samurai->ySpeed = 0;
        samurai->isJumping = false;
    }

    // Border collision
    if (samurai->position.x < 0)
        samurai->position.x = 0;
    if (samurai->position.x > SCREEN_WIDTH - SAMURAI_FRAME_SIZE)
        samurai->position.x = SCREEN_WIDTH - SAMURAI_FRAME_SIZE;
    if (samurai->position.y < 0) {
        samurai->position.y = 0;
        samurai->ySpeed = 0;
    }
}

void renderSamurai(Samurai *samurai) {
    Rectangle sourceRect = {samurai->frameIndex * SAMURAI_FRAME_SIZE, 0,
                            samurai->facingRight ? SAMURAI_FRAME_SIZE
                                                 : -SAMURAI_FRAME_SIZE,
                            SAMURAI_FRAME_SIZE};

    Rectangle destRect = {samurai->position.x, samurai->position.y,
                          SAMURAI_FRAME_SIZE, SAMURAI_FRAME_SIZE};

    DrawTexturePro(samurai->idleTexture, sourceRect, destRect, (Vector2){0, 0},
                   0.0f, WHITE);
}
