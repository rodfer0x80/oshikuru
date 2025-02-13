#ifndef NPC_H
#define NPC_H

#include "stddef.h"
#include "string.h"

#include "raylib.h"

#include "config.h"

typedef struct NPC {
    Rectangle rect;
    Color color;
    int damage;
    int hitpoints;
} NPC;

typedef struct NPCS {
    NPC units[MAX_NPCS];
    int count;
} NPCS;

void newNPC(NPCS *npcs, Vector2 *position, int width, int height, Color color,
             int damage);
void resetNPCS(NPCS *npcs);

void npcsLevel0(NPCS *npcs);
void npcsLevel1(NPCS *npcs);

#endif // NPC_H
