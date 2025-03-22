#ifndef RENDER_H
#define RENDER_H

//#include "raylib.h"

//#include "config.h"
#include "entities/npc.h"
#include "world/platform.h"
#include "world/portal.h"
#include "entities/samurai.h"

void renderGame(Samurai *samurai, Platforms *platforms, Fires *fires,
                Portal *portal, NPCS *npcs, float *timer);

void renderMenu(Samurai *samurai);

void renderSamurai(Samurai *samurai);

void renderNPC(NPC *npc);
void renderNPCS(NPCS *npcs);

void renderPortal(Portal *portal);

void renderVictory();

void renderDefeat();

#endif // RENDER_H
