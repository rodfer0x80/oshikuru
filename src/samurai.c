#include "raylib.h"

#include "config.h"
#include "platform.h"
#include "portal.h"
#include "samurai.h"

void updateSamuraiAnimation(Samurai *samurai) {
    samurai->animation.frameCounter += GetFrameTime() * SAMURAI_ANIMATION_SPEED;
    if (samurai->animation.frameCounter >= 1.0f) {
        int frameCount;
        if (samurai->state.isHurt) {
            frameCount = SAMURAI_HURT_FRAME_COUNT;
        } else if (samurai->state.isAttacking) {
            frameCount = SAMURAI_ATTACK_FRAME_COUNT;
        } else if (samurai->state.isRunning) {
            frameCount = SAMURAI_RUN_FRAME_COUNT;
        } else {
            frameCount = SAMURAI_IDLE_FRAME_COUNT;
        }

        samurai->animation.frameIndex++;
        samurai->animation.frameCounter = 0.0f;

        if (samurai->state.isHurt &&
            samurai->animation.frameIndex >= SAMURAI_HURT_FRAME_COUNT) {
            samurai->state.isHurt = false;
            samurai->animation.frameIndex = 0;
        } else if (samurai->state.isAttacking &&
                   samurai->animation.frameIndex >=
                       SAMURAI_ATTACK_FRAME_COUNT) {
            samurai->state.isAttacking = false;
            samurai->animation.frameIndex = 0;
        } else {
            samurai->animation.frameIndex %= frameCount;
        }
    }
}

void updateSamuraiMovement(Samurai *samurai) {
    if (samurai->state.isHurt) {
        samurai->state.isAttacking = false;
    }

    bool isMoving = false;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        samurai->position.x -= samurai->speed.x;
        samurai->state.facingLeft = true;
        isMoving = true;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        samurai->position.x += samurai->speed.x;
        samurai->state.facingLeft = false;
        isMoving = true;
    }
    samurai->state.isRunning = isMoving;

    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) &&
        !samurai->state.isJumping && !samurai->state.isAttacking) {
        samurai->speed.y = samurai->stats.jumpStrength;
        samurai->state.isJumping = true;
    }

    if (IsKeyPressed(KEY_SPACE) && !samurai->state.isAttacking) {
        samurai->state.isAttacking = true;
        samurai->animation.frameIndex = 0;
        samurai->animation.attackFrame = 0.0f;
    }

    if (DEBUG_RAYLIB && IsKeyPressed(KEY_C) && !samurai->state.isHurt) {
        samurai->state.isHurt = true;
        samurai->stats.hitpoints -= 1;
        if (samurai->stats.hitpoints <= 0) {
            samurai->state.isDead = true;
        }
    }
    if (DEBUG_RAYLIB && IsKeyPressed(KEY_X) && !samurai->state.isHurt) {
        samurai->state.isHurt = true;
        samurai->stats.hitpoints -= SAMURAI_MAX_HITPOINTS;
        if (samurai->stats.hitpoints <= 0) {
            samurai->state.isDead = true;
        }
    }
}

void updateSamuraiPhysics(Samurai *samurai, Platforms *platforms,
                          Fires *fires) {
    samurai->speed.y += samurai->stats.gravityEffect;
    samurai->position.y += samurai->speed.y;

    if (samurai->state.isAttacking &&
        samurai->animation.frameIndex == SAMURAI_SLASH_FRAME &&
        !samurai->slash.isActive) {
        // TODO: sep and add to slash instead of doing a mash and converting to
        // a slash
        samurai->slash = (SamuraiSlash){
            {samurai->position.x + SAMURAI_X_MOD +
                 (samurai->state.facingLeft ? -SAMURAI_ATTACK_RANGE : 0),
             samurai->position.y + SAMURAI_Y_MOD},
            SAMURAI_X_REC + SAMURAI_ATTACK_RANGE,
            SAMURAI_Y_REC,
            samurai->stats.damage,
            true};
    } else if (samurai->animation.frameIndex < SAMURAI_SLASH_FRAME ||
               samurai->animation.frameIndex >= SAMURAI_ATTACK_FRAME_COUNT) {
        samurai->slash.isActive = false;
    }

    bool onPlatform = false;
    for (int i = 0; i < platforms->count; i++) {
        Rectangle samuraiRect = {samurai->position.x + SAMURAI_X_SLIM_MOD,
                                 samurai->position.y + SAMURAI_Y_SLIM_MOD,
                                 SAMURAI_X_SLIM_REC, SAMURAI_Y_SLIM_REC};

        
        if (CheckCollisionRecs(samuraiRect, platforms->units[i].rect)) {
            if (samurai->speed.y > 0 &&
                samurai->position.y + SAMURAI_Y_MOD + SAMURAI_Y_REC >=
                    platforms->units[i].rect.y) {
                samurai->position.y =
                    platforms->units[i].rect.y - SAMURAI_Y_MOD - SAMURAI_Y_REC;
                samurai->speed.y = 0;
                onPlatform = true;
                if (samurai->state.isJumping) {
                    samurai->state.isJumping = false;
                }
            }
        }
    }

    for (int i = 0; i < fires->count; i++) {
        if (!samurai->state.isHurt) {
            Rectangle samuraiRect = {samurai->position.x + SAMURAI_X_SLIM_MOD,
                                     samurai->position.y + SAMURAI_Y_SLIM_MOD,
                                     SAMURAI_X_SLIM_REC, SAMURAI_Y_SLIM_REC};
            if (CheckCollisionRecs(samuraiRect, fires->units[i].rect)) {
                samurai->state.isHurt = true;
                samurai->stats.hitpoints -= fires->units[i].damage;
                if (samurai->stats.hitpoints <= 0) {
                    samurai->state.isDead = true;
                }
            }
        }
    }

    if (!onPlatform &&
        samurai->position.y - SAMURAI_Y_MOD - SAMURAI_Y_REC < SCREEN_HEIGHT) {
        samurai->state.isJumping = true;
    }

    if (samurai->position.x <= 0 - SAMURAI_X_MOD)
        samurai->position.x = 0 - SAMURAI_X_MOD;
    if (samurai->position.x >= SCREEN_WIDTH - SAMURAI_X_MOD - SAMURAI_X_REC)
        samurai->position.x = SCREEN_WIDTH - SAMURAI_X_MOD - SAMURAI_X_REC;
    if (samurai->position.y <= 0 - SAMURAI_Y_MOD) {
        samurai->position.y = 0 - SAMURAI_Y_MOD;
        samurai->speed.y = 0;
    }
    if (samurai->position.y >= SCREEN_HEIGHT - SAMURAI_Y_MOD - SAMURAI_Y_REC) {
        samurai->position.y = SCREEN_HEIGHT - SAMURAI_Y_MOD - SAMURAI_Y_REC;
        samurai->speed.y = 0;
    }
}

void updateSamurai(Samurai *samurai, Platforms *platforms, Fires *fires) {
    updateSamuraiAnimation(samurai);
    updateSamuraiMovement(samurai);
    updateSamuraiPhysics(samurai, platforms, fires);
}

bool samuraiPassesPortal(Samurai *samurai, Portal *portal) {
    Rectangle samuraiRect = {samurai->position.x + SAMURAI_X_MOD,
                             samurai->position.y + SAMURAI_Y_MOD, SAMURAI_X_REC,
                             SAMURAI_Y_REC};
    return CheckCollisionRecs(samuraiRect, portal->rect);
}

void renderSamurai(Samurai *samurai) {
    Rectangle sourceRect = {
        samurai->animation.frameIndex * SAMURAI_FRAME_SIZE, 0,
        samurai->state.facingLeft ? -SAMURAI_FRAME_SIZE : SAMURAI_FRAME_SIZE,
        SAMURAI_FRAME_SIZE};
    Rectangle destRect = {samurai->position.x, samurai->position.y,
                          SAMURAI_FRAME_SIZE, SAMURAI_FRAME_SIZE};

    Texture2D texture;
    if (samurai->state.isHurt) {
        texture = samurai->animation.assets.hurtTexture;
    } else if (samurai->state.isAttacking) {
        texture = samurai->animation.assets.attackTexture;
    } else if (samurai->state.isRunning) {
        texture = samurai->animation.assets.runTexture;
    } else {
        texture = samurai->animation.assets.idleTexture;
    }

    DrawTexturePro(texture, sourceRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
}
