#include "entities/npc.h"

void removeNPC(NPCS *npcs, int n) {
    for (int j = n; j < npcs->count - 1; j++) {
        npcs->units[j] = npcs->units[j + 1];
    }
    npcs->count--;
}

void updateNPCS(NPCS *npcs, Samurai *samurai) {
    // TODO: make samuraiSlash rec a thing
    Rectangle samuraiSlashRec = {samurai->slash.position.x,
                                 samurai->slash.position.y,
                                 samurai->slash.width, samurai->slash.height};

    if (samurai->slash.isActive) {
        float initHitpoints;
        float diffHitpoints;
        for (int i = 0; i < npcs->count; i++) {
            initHitpoints = npcs->units[i].hitpoints;
            if (CheckCollisionRecs(samuraiSlashRec, npcs->units[i].rect)) {
                npcs->units[i].hitpoints -= samurai->slash.damage;
                diffHitpoints = initHitpoints - npcs->units[i].hitpoints;
                if (diffHitpoints) {
                    TraceLog(LOG_INFO, TextFormat("[NPC%d] Damage Taken %.0f, "
                                                  "Current Hitpoints: %.0f",
                                                  i, diffHitpoints,
                                                  npcs->units[i].hitpoints));
                }
                if (npcs->units[i].hitpoints <= 0) {
                    removeNPC(npcs, i);
                    i--;
                }
            }
        }
    }
}

void newNPC(NPCS *npcs, Vector2 *position, int width, int height, Color color,
            float hitpoints, float damage) {
    if (npcs->count < MAX_NPCS) {
        npcs->units[npcs->count] =
            (NPC){(Rectangle){position->x, position->y, width, height}, color,
                  hitpoints, damage};
        npcs->count++;
    } else {
        TraceLog(LOG_ERROR, TextFormat("%s:%d -> "
                                       "Max number reached: %d == %d " __FILE__,
                                       __LINE__, npcs->count, MAX_FIRES));
    }
}

void resetNPCS(NPCS *npcs) {
    npcs->count = 0;
    memset(npcs->units, 0, MAX_NPCS * sizeof(NPC));
}

void npcsLevel0(NPCS *npcs) {
    int npcWidth = 40;
    int npcHeight = 40;
    Vector2 npc1Position = {200, SCREEN_HEIGHT - npcHeight - 20};
    Vector2 npc2Position = {400, SCREEN_HEIGHT - npcHeight - 20};
    Color npcColor = PURPLE;
    float npcDamage = 10.0f;
    float npcHitpoints = 100.0f;

    resetNPCS(npcs);

    newNPC(npcs, &npc1Position, npcWidth, npcHeight, npcColor, npcHitpoints,
           npcDamage);
    newNPC(npcs, &npc2Position, npcWidth, npcHeight, npcColor, npcHitpoints,
           npcDamage);
}

void npcsLevel1(NPCS *npcs) {
    int npcWidth = SCREEN_WIDTH;
    int npcHeight = 20;
    Vector2 npc1Position = {0, SCREEN_WIDTH - npcHeight};
    Color npcColor = PURPLE;
    float npcDamage = 10.0f;
    float npcHitpoints = 100.0f;

    resetNPCS(npcs);

    newNPC(npcs, &npc1Position, npcWidth, npcHeight, npcColor, npcHitpoints,
           npcDamage);
}
