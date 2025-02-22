#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "config/config.h"
#include "characters/npc.h"
#include "map/platform.h"
#include "map/portal.h"
#include "characters/samurai.h"

void renderGame(Samurai *samurai, Platforms *platforms, Fires *fires,
                Portal *portal, NPCS *npcs, float *timer);

void renderMenu(Samurai *samurai);

void renderSamurai(Samurai *samurai);

void renderVictory();

void renderDefeat();

#endif // GAME_H
