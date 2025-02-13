#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "config.h"
#include "npc.h"
#include "platform.h"
#include "portal.h"
#include "samurai.h"

void renderGame(Samurai *samurai, Platforms *platforms, Fires *fires,
                Portal *portal, NPCS *npcs, float *timer);

void renderMenu(Samurai *samurai);

void renderSamurai(Samurai *samurai);

void renderVictory();

void renderDefeat();

#endif // GAME_H
