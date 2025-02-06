#include "game.h"
#include "config.h"
#include "samurai.h"

void renderGame(Samurai *samurai) {
    ClearBackground(GRAY);
    Rectangle groundPlatform = {0, SCREEN_HEIGHT / 2 + SAMURAI_FRAME_SIZE / 3,
                                SCREEN_WIDTH, 8};
    DrawRectangleLinesEx(groundPlatform, 8, DARKBLUE);
    renderSamurai(samurai);
}

void renderMenu(Samurai *samurai) {
    samurai->position.x = SCREEN_WIDTH / 2 - SAMURAI_FRAME_SIZE / 2;
    samurai->position.y = SCREEN_HEIGHT / 2 - SAMURAI_FRAME_SIZE / 2;
    samurai->facingRight = true;
    Rectangle menuBorder = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    ClearBackground(GRAY);
    DrawText("PRESS <ESQ> TO QUIT", 60, 60, 20, DARKBLUE);
    DrawText("OSHIKURU", 380, 240, 80, DARKBLUE);
    DrawText("PRESS <ENTER> TO PLAY", 400, 600, 30, DARKBLUE);
    DrawRectangleLinesEx(menuBorder, 8, DARKBLUE);
    renderSamurai(samurai);
}
