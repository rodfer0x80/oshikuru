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
    Samurai menuSamurai = {
        {SCREEN_WIDTH / 2 - SAMURAI_FRAME_SIZE / 2,
         SCREEN_HEIGHT / 2 - SAMURAI_FRAME_SIZE / 2}, // position
        8.0f,                                         // xSpeed
        0.0f,                                         // ySpeed
        100,                                          // hitpoints
        -20.0f,                                       // jumpStrength
        1.2f,                                         // gravityEffect
        samurai->idleTexture,                         // idleTexture
        samurai->runTexture,                          // runTexture
        samurai->attackTexture,                       // attackTexture
        0,                                            // frameIndex
        0.0f,                                         // frameCounter
        false,                                        // facingLeft
        false,                                         // isRunning
        false,                                        // isJumping
        false,                                        // isAttacking
        false,                                        // isHurt
        false                                         // isDead
    };
    Rectangle menuBorder = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    ClearBackground(GRAY);
    DrawText("PRESS <ESQ> TO QUIT", 60, 60, 20, DARKBLUE);
    DrawText("OSHIKURU", 400, 240, 80, DARKBLUE);
    DrawText("PRESS <ENTER> TO PLAY", 400, 560, 30, DARKBLUE);
    DrawRectangleLinesEx(menuBorder, 8, DARKBLUE);
    renderSamurai(&menuSamurai);
}

void renderEndgame() {
    Rectangle menuBorder = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    ClearBackground(GRAY);
    DrawText("PRESS <ESQ> TO QUIT", 60, 60, 20, DARKBLUE);
    DrawText("YOU HAVE DIED", 260, 400, 80, DARKBLUE);
    DrawRectangleLinesEx(menuBorder, 8, DARKBLUE);
}
