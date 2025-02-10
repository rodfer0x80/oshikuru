#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "samurai.h"

void renderGame(Samurai *samurai, Platforms *platforms, Fires *fires,
                Portal *portal);
void renderMenu(Samurai *samurai);
void renderVictory();
void renderDefeat();

#endif // GAME_H
