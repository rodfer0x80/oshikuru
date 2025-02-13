#include "game.h"
#include "config.h"
#include "platform.h"
#include "portal.h"
#include "samurai.h"

void renderGame(Samurai *samurai, Platforms *platforms, Fires *fires,
                Portal *portal, float *timer) {
    ClearBackground(GRAY);

    DrawText(TextFormat("[HP: %d]", samurai->stats.hitpoints), SCREEN_WIDTH - 180, 40, 40,
             DARKBLUE);
    
    *timer += GetFrameTime();
    DrawText(TextFormat("[T: %.0f]", *timer), 40, 40, 40,
             DARKBLUE);

    for (int i = 0; i < platforms->count; i++) {
        DrawRectangleRec(platforms->units[i].rect, platforms->units[i].color);
        if (DEBUG_RAYLIB)
            DrawRectangleLinesEx(platforms->units[i].rect, 2, WHITE);
    }

    for (int i = 0; i < fires->count; i++) {
        DrawRectangleRec(fires->units[i].rect, fires->units[i].color);
        if (DEBUG_RAYLIB)
            DrawRectangleLinesEx(fires->units[i].rect, 2, WHITE);
    }

    DrawRectangleRec(portal->rect, portal->color);
    if (DEBUG_RAYLIB)
        DrawRectangleLinesEx(portal->rect, 2, PINK);

    renderSamurai(samurai);
    if (DEBUG_RAYLIB) {
        Rectangle samuraiRect = {samurai->position.x + SAMURAI_X_MOD,
                                 samurai->position.y + SAMURAI_Y_MOD,
                                 SAMURAI_X_REC, SAMURAI_Y_REC};
        DrawRectangleLinesEx(samuraiRect, 2, RED);

        Rectangle samuraiPlatformRect = {
            samurai->position.x + SAMURAI_X_SLIM_MOD,
            samurai->position.y + SAMURAI_Y_SLIM_MOD, SAMURAI_X_SLIM_REC,
            SAMURAI_Y_SLIM_REC};
        DrawRectangleLinesEx(samuraiPlatformRect, 2, ORANGE);

        Rectangle samuraiSlashRect = {
            samurai->slash.position.x, samurai->slash.position.y,
            samurai->slash.width, samurai->slash.height};
        if (samurai->slash.isActive) {
            DrawRectangleLinesEx(samuraiSlashRect, 2, YELLOW);
        }
    }
}

void renderMenu(Samurai *samurai) {
    Samurai menuSamurai = {
        .position = {SCREEN_WIDTH / 2.0f - SAMURAI_FRAME_SIZE / 2.0f,
                     SCREEN_HEIGHT / 2.0f -
                         SAMURAI_FRAME_SIZE / 2.0f},         // position
        .speed = {8.0f, 0.0f},                               // speed
        .stats = {100, 20, -20.0f, 1.2f},                    // stats
        .state = {false, false, false, false, false, false}, // state
        .animation =
            {// animation
             .frameIndex = 0,
             .frameCounter = 0.0f,
             .attackFrame = 0,
             .assets = {samurai->animation.assets.idleTexture,
                        samurai->animation.assets.runTexture,
                        samurai->animation.assets.attackTexture,
                        samurai->animation.assets.hurtTexture}},
        .slash = {{0, 0}, 0.0f, 0.0f, 0, false} // slash
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
