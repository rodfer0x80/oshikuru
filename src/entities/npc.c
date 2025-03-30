#include "entities/npc.h"
#include "entities/samurai.h"

void removeNPC(NPCS *npcs, int n) {
    for (int j = n; j < npcs->count - 1; j++) {
        npcs->units[j] = npcs->units[j + 1];
    }
    npcs->count--;
}

void updateNPCAnimation(NPC *npc, float *deltaTime) {
    // Update tempo
    npc->animation.frameCounter += *deltaTime * NPC_ANIMATION_SPEED;

    // Update animation
    if (npc->animation.frameCounter >= 1.0f) {
        int frameCount;
        if (npc->state.isDead) {
            frameCount = NPC_DEATH_FRAME_COUNT;
        } else if (npc->state.isHurt) {
            frameCount = NPC_HURT_FRAME_COUNT;
        } else if (npc->state.isAttacking) {
            frameCount = NPC_ATTACK_FRAME_COUNT;
        } else if (npc->state.isFlying) {
            frameCount = NPC_FLYING_FRAME_COUNT;
        } else {
            frameCount = NPC_IDLE_FRAME_COUNT;
        }

        npc->animation.frameIndex++;
        npc->animation.frameCounter = 0.0f;

        if (npc->state.isHurt &&
            npc->animation.frameIndex >= NPC_HURT_FRAME_COUNT) {
            npc->state.isHurt = false;
            npc->animation.frameIndex = 0;
        } else if (npc->state.isAttacking &&
                   npc->animation.frameIndex >= NPC_ATTACK_FRAME_COUNT) {
            npc->state.isAttacking = false;
            npc->animation.frameIndex = 0;
        } else if (npc->state.isDead &&
                   npc->animation.frameIndex >= NPC_DEATH_FRAME_COUNT) {
            // Keep the last frame of death animation
            npc->animation.frameIndex = NPC_DEATH_FRAME_COUNT - 1;
        } else {
            npc->animation.frameIndex %= frameCount;
        }
    }
}

void updateNPCS(NPCS *npcs, Samurai *samurai, float *deltaTime) {
    Rectangle samuraiSlashRec = {samurai->slash.position.x,
                                 samurai->slash.position.y,
                                 samurai->slash.width, samurai->slash.height};

    Rectangle samuraiRec = {samurai->position.x + SAMURAI_X_MOD,
                            samurai->position.y + SAMURAI_Y_MOD, SAMURAI_X_REC,
                            SAMURAI_Y_REC};

    if (samurai->slash.isActive) {
        float initHitpoints;
        float diffHitpoints;
        for (int i = 0; i < npcs->count; i++) {
            initHitpoints = npcs->units[i].hitpoints;
            if (CheckCollisionRecs(samuraiSlashRec, npcs->units[i].rect)) {
                npcs->units[i].hitpoints -= samurai->slash.damage;
                npcs->units[i].state.isHurt = true;
                npcs->units[i].animation.frameIndex = 0;
                diffHitpoints = initHitpoints - npcs->units[i].hitpoints;
                if (diffHitpoints) {
                    TraceLog(LOG_INFO, TextFormat("[NPC%d] Damage Taken %.0f, "
                                                  "Current Hitpoints: %.0f",
                                                  i, diffHitpoints,
                                                  npcs->units[i].hitpoints));
                }
                if (npcs->units[i].hitpoints <= 0) {
                    npcs->units[i].state.isDead = true;
                    npcs->units[i].animation.frameIndex = 0;
                    // TODO: this hit is broken, perma animation and no removal
                    // Only remove NPC after death animation completes
                    // if (npcs->units[i].animation.frameIndex >=
                    //     NPC_DEATH_FRAME_COUNT - 1) {
                    //     removeNPC(npcs, i);
                    //     i--;
                    // }
                    // TODO: ----
                    removeNPC(npcs, i); // Temporary bypass
                }
            }

            // Update individual NPC animation
            updateNPCAnimation(&npcs->units[i], deltaTime);
        }
    } else {
        // When not getting hit, still update animations
        for (int i = 0; i < npcs->count; i++) {
            updateNPCAnimation(&npcs->units[i], deltaTime);
        }
    }
}

void newNPC(NPCS *npcs, NPCAssets loadedAssets, Vector2 *position, int width,
            int height, Color color, float hitpoints, float damage) {
    if (npcs->count < MAX_NPCS) {
        NPC npc = {
            .rect = (Rectangle){position->x, position->y, width, height},
            .color = color,
            .hitpoints = hitpoints,
            .damage = damage,
            .position = *position,
            .speed = (Vector2){0, 0},
            .animation = {.frameIndex = 0,
                          .frameCounter = 0.0f,
                          .attackFrame = 0.0f,
                          .assets = {.idleTexture = loadedAssets.idleTexture,
                                     .attackTexture =
                                         loadedAssets.attackTexture,
                                     .hurtTexture = loadedAssets.hurtTexture,
                                     .deathTexture = loadedAssets.deathTexture,
                                     .flyingTexture =
                                         loadedAssets.flyingTexture}},
            .state = {.isIdle = true,
                      .isFlying = false,
                      .isAttacking = false,
                      .isHurt = false,
                      .isDead = false,
                      .facingLeft = false},
            .projectiles = {{}, 0}};

        npcs->units[npcs->count] = npc;
        npcs->count++;
    } else {
        TraceLog(LOG_ERROR,
                 TextFormat("%s:%d -> "
                            "Max number reached: %d == %d",
                            __FILE__, __LINE__, npcs->count, MAX_NPCS));
    }
}

void resetNPCS(NPCS *npcs) {
    npcs->count = 0;
    memset(npcs->units, 0, MAX_NPCS * sizeof(NPC));
}

void npcsLevel0(NPCS *npcs, NPCAssets NPCLoadedAssets) {
    int npcWidth = 40;
    int npcHeight = 40;
    Vector2 npc1Position = {200, SCREEN_HEIGHT - npcHeight - 20 - 20};
    Vector2 npc2Position = {400, SCREEN_HEIGHT - npcHeight - 20 - 20};
    Color npcColor = PURPLE;
    float npcDamage = 10.0f;
    float npcHitpoints = 100.0f;

    resetNPCS(npcs);

    newNPC(npcs, NPCLoadedAssets, &npc1Position, npcWidth, npcHeight, npcColor,
           npcHitpoints, npcDamage);
    newNPC(npcs, NPCLoadedAssets, &npc2Position, npcWidth, npcHeight, npcColor,
           npcHitpoints, npcDamage);
}

void npcsLevel1(NPCS *npcs, NPCAssets NPCLoadedAssets) {
    int npcWidth = SCREEN_WIDTH;
    int npcHeight = 20;
    Vector2 npc1Position = {0, SCREEN_WIDTH - npcHeight};
    Color npcColor = PURPLE;
    float npcDamage = 10.0f;
    float npcHitpoints = 100.0f;

    resetNPCS(npcs);

    newNPC(npcs, NPCLoadedAssets, &npc1Position, npcWidth, npcHeight, npcColor,
           npcHitpoints, npcDamage);
}
