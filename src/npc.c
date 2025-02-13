#include "stddef.h"
#include "string.h"

#include "raylib.h"

#include "config.h"
#include "npc.h"

void newNPC(NPCS *npcs, Vector2 *position, int width, int height, Color color,
            int damage) {
    if (npcs->count < MAX_FIRES) {
        npcs->units[npcs->count] =
            (NPC){(Rectangle){position->x, position->y, width, height}, color,
                  damage};
        npcs->count++;
    } else {
        TraceLog(LOG_ERROR, TextFormat("[Error] %s:%d -> "
                                       "Max number reached: %d == %d " __FILE__,
                                       __LINE__, npcs->count, MAX_FIRES));
    }
}

void resetNPCS(NPCS *npcs) {
    npcs->count = 0;
    memset(npcs->units, 0, MAX_FIRES * sizeof(NPC));
}

void npcsLevel0(NPCS *npcs) {
    int npcWidth = 100;
    int npcHeight = 20;
    Vector2 npc1Position = {200, 350 - npcHeight};
    Vector2 npc2Position = {400, 350 - npcHeight};
    Color npcColor = ORANGE;
    int npcDamage = 10;

    resetNPCS(npcs);

    newNPC(npcs, &npc1Position, npcWidth, npcHeight, npcColor, npcDamage);
    newNPC(npcs, &npc2Position, npcWidth, npcHeight, npcColor, npcDamage);
}

void npcsLevel1(NPCS *npcs) {
    int npcWidth = SCREEN_WIDTH;
    int npcHeight = 20;
    Vector2 npc1Position = {0, SCREEN_WIDTH - npcHeight};
    Color npcColor = ORANGE;
    int npcDamage = 2;

    resetNPCS(npcs);

    newNPC(npcs, &npc1Position, npcWidth, npcHeight, npcColor, npcDamage);
}
