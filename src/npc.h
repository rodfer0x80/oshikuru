#ifndef NPC_H
#define NPC_H

#include "stddef.h"
#include "string.h"

#include "raylib.h"

#include "config.h"
#include "samurai.h"

typedef struct NPC {
    Rectangle rect;
    Color color;
    float hitpoints;
    float damage;
} NPC;

typedef struct NPCS {
    NPC units[MAX_NPCS];
    int count;
} NPCS;

void removeNPC(NPCS *npcs, int n);
void updateNPCS(NPCS *npcs, Samurai *samurai);
void newNPC(NPCS *npcs, Vector2 *position, int width, int height, Color color,
             float hitpoints, float damage);
void resetNPCS(NPCS *npcs);

void npcsLevel0(NPCS *npcs);
void npcsLevel1(NPCS *npcs);

#endif // NPC_H
