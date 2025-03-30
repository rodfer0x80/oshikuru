#include "entities/samurai.h"

void samuraiHitFor(Samurai *samurai, float damage) {
    float diffHitpoints;
    float initHitpoints;
    initHitpoints = samurai->stats.hitpoints;
    if (!samurai->state.isImmune) {
        if (!samurai->state.isHurt) {
            samurai->state.isHurt = true;
            samurai->stats.hitpoints -= damage;
            if (samurai->stats.hitpoints <= 0.0)
                samurai->state.isDead = true;
            diffHitpoints = initHitpoints - samurai->stats.hitpoints;
            TraceLog(LOG_INFO,
                     TextFormat("[Samurai] Damage Taken %.0f, "
                                "Current Hitpoints: %.0f",
                                diffHitpoints, samurai->stats.hitpoints));
        }
    }
}

void updateSamuraiAnimation(Samurai *samurai, float *deltaTime) {
    // Update tempo
    samurai->animation.frameCounter += *deltaTime * SAMURAI_ANIMATION_SPEED;
    // ----

    // Update animation
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
    // ----
}

void updateSamuraiMovement(Samurai *samurai) {
    // Disable attacking while hurt animation is running
    if (samurai->state.isHurt)
        samurai->state.isAttacking = false;
    // ----

    // Controls
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
        !samurai->state.isJumping) {
        samurai->speed.y = samurai->stats.jumpStrength;
        samurai->state.isJumping = true;
    }
    if (IsKeyPressed(KEY_SPACE) && !samurai->state.isAttacking) {
        samurai->state.isAttacking = true;
        samurai->animation.frameIndex = 0;
        samurai->animation.attackFrame = 0.0f;
    }
    // ----

    // DEBUG controls
    if (DEBUG_RAYLIB && IsKeyPressed(KEY_C) && !samurai->state.isHurt) {
        samuraiHitFor(samurai, 10.0f);
    }
    if (DEBUG_RAYLIB && IsKeyPressed(KEY_X)) {
        samurai->state.isHurt = true;
        samurai->stats.hitpoints -= SAMURAI_MAX_HITPOINTS;
        if (samurai->stats.hitpoints <= 0.0)
            samurai->state.isDead = true;
    }
    if (DEBUG_RAYLIB && IsKeyPressed(KEY_H))
        samurai->stats.hitpoints = SAMURAI_MAX_HITPOINTS;
    if (DEBUG_RAYLIB && IsKeyPressed(KEY_I))
        samurai->state.isImmune = !samurai->state.isImmune;
    // ----
}

void updateSamuraiPhysics(Samurai *samurai, Platforms *platforms,
                          Fires *fires, NPCS *npcs) {
    // Update slim rectangle
    Rectangle samuraiSlimRec = {samurai->position.x + SAMURAI_X_SLIM_MOD,
                                samurai->position.y + SAMURAI_Y_SLIM_MOD,
                                SAMURAI_X_SLIM_REC, SAMURAI_Y_SLIM_REC};
    samurai->hitbox.slimRec = samuraiSlimRec;
    // ----

    // Update gravity application
    samurai->speed.y += samurai->stats.gravityEffect;
    samurai->position.y += samurai->speed.y;
    // ----

    // Samurai X NPC collision damages Samurai for flat 5hp
        if (!samurai->state.isHurt) {
            for (int i = 0; i < npcs->count; i++) {
                if (CheckCollisionRecs(samurai->hitbox.rec, npcs->units[i].rect)) {
                    samuraiHitFor(samurai, 10);
                    break;
                }
            }
        }
    // ----

    // Attack physics
    // Slash applies damage 10x per attack
    if (samurai->state.isAttacking &&
        samurai->animation.frameIndex == SAMURAI_SLASH_FRAME &&
        !samurai->slash.isActive) {
        SamuraiSlash samuraiSlash = {
            {samurai->position.x + SAMURAI_X_MOD +
                 (samurai->state.facingLeft ? -SAMURAI_ATTACK_RANGE : 0),
             samurai->position.y + SAMURAI_Y_MOD},
            SAMURAI_X_REC + SAMURAI_ATTACK_RANGE,
            SAMURAI_Y_REC,
            samurai->stats.damage / SAMURAI_SLASH_FRAME_COUNT,
            true};
        samurai->slash = samuraiSlash;
    } else if (samurai->animation.frameIndex < SAMURAI_SLASH_FRAME ||
               samurai->animation.frameIndex >= SAMURAI_ATTACK_FRAME_COUNT) {
        samurai->slash.isActive = false;
    }
    // ----

    // Map platform collision physics
    bool onPlatform = false;
    for (int i = 0; i < platforms->count; i++) {
        if (CheckCollisionRecs(samurai->hitbox.slimRec,
                               platforms->units[i].rect)) {
            if (samurai->speed.y > 0 &&
                samurai->position.y + SAMURAI_Y_MOD + SAMURAI_Y_REC >=
                    platforms->units[i].rect.y) {
                samurai->position.y =
                    platforms->units[i].rect.y - SAMURAI_Y_MOD - SAMURAI_Y_REC;
                samurai->speed.y = 0;
                onPlatform = true;
                samurai->state.isJumping = false;
            }
        }
    }
    // ----

    // Map fire collision physics
    for (int i = 0; i < fires->count; i++) {
        if (CheckCollisionRecs(samurai->hitbox.slimRec, fires->units[i].rect)) {
            samuraiHitFor(samurai, fires->units[i].damage);
        }
    }
    // ----

    // Jump detection
    if (!onPlatform &&
        samurai->position.y - SAMURAI_Y_MOD - SAMURAI_Y_REC < SCREEN_HEIGHT) {
        samurai->state.isJumping = true;
    }
    // ----

    // Map border collision
    if (samurai->position.x <= 0 - SAMURAI_X_MOD)
        samurai->position.x = 0 - SAMURAI_X_MOD;
    if (samurai->position.x >= SCREEN_WIDTH - SAMURAI_X_MOD - SAMURAI_X_REC)
        samurai->position.x = SCREEN_WIDTH - SAMURAI_X_MOD - SAMURAI_X_REC;
    if (samurai->position.y <= 0 - SAMURAI_Y_MOD)
        samurai->position.y = 0 - SAMURAI_Y_MOD;
    if (samurai->position.y >= SCREEN_HEIGHT - SAMURAI_Y_MOD - SAMURAI_Y_REC) {
        samurai->position.y = SCREEN_HEIGHT - SAMURAI_Y_MOD - SAMURAI_Y_REC;
        samurai->speed.y = 0;
    }
    // ----
}

void updateSamurai(Samurai *samurai, Platforms *platforms, Fires *fires, NPCS *npcs,
                   float *deltaTime) {
    updateSamuraiAnimation(samurai, deltaTime);
    updateSamuraiMovement(samurai);
    updateSamuraiPhysics(samurai, platforms, fires, npcs);
    if (samurai->state.isDead) {
        if (--samurai->stats.lives > 0) {
            TraceLog(LOG_INFO, TextFormat("[Samurai] Life lost, %d remaining",
                                          samurai->stats.lives));
            samurai->state.isDead = false;
            samurai->stats.hitpoints = SAMURAI_MAX_HITPOINTS;
            samurai->state.hasDied = true;
        } else {
            TraceLog(LOG_INFO,
                     TextFormat("[Samurai] Dead, no more lives remaining"));
        }
    }
}

bool samuraiPassesPortal(Samurai *samurai, Portal *portal) {
    // Update samurai rec hitbox
    Rectangle samuraiRec = {samurai->position.x + SAMURAI_X_MOD,
                            samurai->position.y + SAMURAI_Y_MOD, SAMURAI_X_REC,
                            SAMURAI_Y_REC};
    samurai->hitbox.rec = samuraiRec;
    // ----
    return CheckCollisionRecs(samurai->hitbox.rec, portal->rec);
}
