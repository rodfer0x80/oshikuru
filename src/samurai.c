#include "raylib.h"

#include "config.h"
#include "platform.h"
#include "samurai.h"

void updateSamurai(Samurai *samurai) {
    // Animation update
    samurai->frameCounter += GetFrameTime() * SAMURAI_ANIMATION_SPEED;
    if (samurai->frameCounter >= 1.0f) {
        int frameCount;
        if (samurai->isAttacking) {
            frameCount = SAMURAI_ATTACK_FRAME_COUNT;
        } else if (samurai->isHurt) {
            frameCount = SAMURAI_HURT_FRAME_COUNT;
        } else if (samurai->isRunning) {
            frameCount = SAMURAI_RUN_FRAME_COUNT;
        } else {
            frameCount = SAMURAI_IDLE_FRAME_COUNT;
        }

        samurai->frameIndex++;
        samurai->frameCounter = 0.0f;

        if (samurai->isAttacking &&
            samurai->frameIndex >= SAMURAI_ATTACK_FRAME_COUNT) {
            samurai->isAttacking = false;
            samurai->frameIndex = 0;
        } else if (samurai->isHurt &&
                   samurai->frameIndex >= SAMURAI_HURT_FRAME_COUNT) {
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
        samurai->facingLeft = true;
        isMoving = true;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        samurai->position.x += samurai->xSpeed;
        samurai->facingLeft = false;
        isMoving = true;
    }
    samurai->isRunning = isMoving;

    // Jump
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && !samurai->isJumping) {
        samurai->ySpeed = samurai->jumpStrength;
        samurai->xSpeed += 2;
        samurai->isJumping = true;
    }

    // Attack
    if (IsKeyPressed(KEY_SPACE) && !samurai->isAttacking) {
        samurai->isAttacking = true;
    }

    // Hurt (debug)
    if (DEBUG_RAYLIB) {
        if (IsKeyPressed(KEY_C) && !samurai->isHurt) {
            samurai->isHurt = true;
            samurai->hitpoints -= 20;
            if (samurai->hitpoints <= 0) {
                samurai->isDead = true;
            }
        }
    }

    // Apply gravity
    samurai->ySpeed += samurai->gravityEffect;
    samurai->position.y += samurai->ySpeed;

    // Platform collision detection
    bool onPlatform = false;
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        Rectangle samuraiRect = {samurai->position.x + SAMURAI_X_MOD,
                                 samurai->position.y + SAMURAI_Y_MOD,
                                 SAMURAI_X_REC, SAMURAI_Y_REC};

        if (CheckCollisionRecs(samuraiRect, platforms[i].rect)) {
            if (samurai->ySpeed > 0 &&
                samurai->position.y + SAMURAI_Y_MOD + SAMURAI_Y_REC >=
                    platforms[i].rect.y) {
                // Land on the platform
                samurai->position.y =
                    platforms[i].rect.y - SAMURAI_Y_MOD - SAMURAI_Y_REC;
                samurai->ySpeed = 0;
                onPlatform = true;
                if (samurai->isJumping) {
                    samurai->xSpeed = 8;
                    samurai->isJumping = false;
                }
            }
        }
    }
    
    if (!onPlatform && samurai->position.y - SAMURAI_Y_MOD - SAMURAI_Y_REC  < SCREEN_HEIGHT / 2 - SAMURAI_FRAME_SIZE / 2) {
        samurai->isJumping = true;
        samurai->xSpeed = 10;
    }

    // Border collision
    if (samurai->position.x <= 0 - SAMURAI_X_MOD)
        samurai->position.x = 0 - SAMURAI_X_MOD;
    if (samurai->position.x >= SCREEN_WIDTH - SAMURAI_X_MOD - SAMURAI_X_REC)
        samurai->position.x = SCREEN_WIDTH - SAMURAI_X_MOD - SAMURAI_X_REC;
    if (samurai->position.y <= 0 - SAMURAI_Y_MOD) {
        samurai->position.y = 0 - SAMURAI_Y_MOD;
        samurai->ySpeed = 0;
    }
    if (samurai->position.y >= SCREEN_HEIGHT - SAMURAI_Y_MOD - SAMURAI_Y_REC) {
        samurai->position.y = SCREEN_HEIGHT - SAMURAI_Y_MOD - SAMURAI_Y_REC;
        samurai->ySpeed = 0;
        if (samurai->isJumping) {
            samurai->xSpeed = 10;
        }
    }
}

void renderSamurai(Samurai *samurai) {
    Rectangle sourceRect = {samurai->frameIndex * SAMURAI_FRAME_SIZE, 0,
                            samurai->facingLeft ? -SAMURAI_FRAME_SIZE
                                                : SAMURAI_FRAME_SIZE,
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
