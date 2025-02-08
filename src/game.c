#include "game.h"
#include "config.h"
#include "platform.h"
#include "portal.h"
#include "samurai.h"

void renderGame(Samurai *samurai) {
    ClearBackground(GRAY);

    DrawText(TextFormat("HP: %d", samurai->hitpoints), 40, 40, 40, DARKBLUE);

    for (int i = 0; i < platformCount; i++) {
        DrawRectangleRec(platforms[i].rect, platforms[i].color);
        if (DEBUG_RAYLIB)
            DrawRectangleLinesEx(platforms[i].rect, 2, ORANGE);
    }

    DrawRectangleRec(portal.rect, portal.color);
    if (DEBUG_RAYLIB)
        DrawRectangleLinesEx(portal.rect, 2, PINK);

    renderSamurai(samurai);
    if (DEBUG_RAYLIB) {
        Rectangle samuraiSlashRect = {samurai->slash.position.x, samurai->slash.position.y,
                                           samurai->slash.width,
                                           samurai->slash.height};
        if (samurai->slash.isActive) {
            DrawRectangleLinesEx(samuraiSlashRect, 2, YELLOW);
        }
    }
    if (DEBUG_RAYLIB) {
        Rectangle samuraiRect = {samurai->position.x + SAMURAI_X_MOD,
                                 samurai->position.y + SAMURAI_Y_MOD,
                                 SAMURAI_X_REC, SAMURAI_Y_REC};
        DrawRectangleLinesEx(samuraiRect, 2, RED);
    }
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
        false,                                        // isRunning
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

void renderVictory() {
    Rectangle menuBorder = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    ClearBackground(GRAY);
    DrawText("PRESS <ESQ> TO QUIT", 60, 60, 20, DARKBLUE);
    DrawText("YOU HAVE WON", 260, 400, 80, DARKBLUE);
    DrawRectangleLinesEx(menuBorder, 8, DARKBLUE);
}

void renderDefeat() {
    Rectangle menuBorder = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    ClearBackground(GRAY);
    DrawText("PRESS <ESQ> TO QUIT", 60, 60, 20, DARKBLUE);
    DrawText("YOU HAVE DIED", 260, 400, 80, DARKBLUE);
    DrawRectangleLinesEx(menuBorder, 8, DARKBLUE);
}
