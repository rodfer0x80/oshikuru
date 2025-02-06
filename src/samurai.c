#include "raylib.h"

#include "config.h"
#include "samurai.h"

void updateSamurai(Samurai *samurai) {
    // Animation update
    samurai->frameCounter += GetFrameTime() * SAMURAI_ANIMATION_SPEED;
    if (samurai->frameCounter >= 1.0f) {
        int frameCount;
        if (samurai->isRunning) {
            frameCount = SAMURAI_RUN_FRAME_COUNT;
        } else if (samurai->isAttacking) {
            frameCount = SAMURAI_ATTACK_FRAME_COUNT;
        } else if (samurai->isHurt) {
            frameCount = SAMURAI_HURT_FRAME_COUNT;
        } else {
            frameCount = SAMURAI_IDLE_FRAME_COUNT;
        }
        
        samurai->frameIndex++;
        samurai->frameCounter = 0.0f;

        if (samurai->isAttacking && samurai->frameIndex >= SAMURAI_ATTACK_FRAME_COUNT) {
            samurai->isAttacking = false;
            samurai->frameIndex = 0; 
        } else if (samurai->isHurt && samurai->frameIndex >= SAMURAI_HURT_FRAME_COUNT) {
            samurai->isHurt = false;
            samurai->frameIndex = 0;
        } else {
            samurai->frameIndex %= frameCount;
        }
    }

    // Movement
    bool isMoving = false;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        samurai->position.x -= samurai->xSpeed;
        samurai->facingLeft = false;
        isMoving = true;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        samurai->position.x += samurai->xSpeed;
        samurai->facingLeft = true;
        isMoving = true;
    }
    samurai->isRunning = isMoving;

    // Jump
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && !samurai->isJumping) {
        samurai->ySpeed = samurai->jumpStrength;
        samurai->isJumping = true;
    }

    // Attack
    if (IsKeyPressed(KEY_SPACE) && !samurai->isAttacking) {
        samurai->isAttacking = true;
    }

    // Hurt (debug)
    if (IsKeyPressed(KEY_C) && !samurai->isHurt) {
        samurai->isHurt = true;
        samurai->hitpoints -= 20;
        if (samurai->hitpoints <= 0) {
            samurai->isDead = true;
        }
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
                            samurai->facingLeft ? SAMURAI_FRAME_SIZE
                                                 : -SAMURAI_FRAME_SIZE,
                            SAMURAI_FRAME_SIZE};

    Rectangle destRect = {samurai->position.x, samurai->position.y,
                          SAMURAI_FRAME_SIZE, SAMURAI_FRAME_SIZE};

    Texture2D texture;
    if (samurai->isHurt) {
        texture = samurai->hurtTexture;
    } else if (samurai->isAttacking) {
        texture = samurai->attackTexture;
    } else if (samurai->isRunning) {
        texture = samurai->runTexture;
    } else {
        texture = samurai->idleTexture;
    }

    DrawTexturePro(texture, sourceRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
}
