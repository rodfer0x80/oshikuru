#include "engine/render.h"

// TODO: change name from game to render for consistency
// TODO: render player and npcs healthbars on top of heads red/black
void renderGame(Samurai *samurai, Platforms *platforms, Fires *fires,
                Portal *portal, NPCS *npcs, float *timer) {
    ClearBackground(GRAY);

    // Draw relevant player stats
    DrawText(TextFormat("[H: %.0f]", samurai->stats.hitpoints),
             SCREEN_WIDTH - 180, 40, 40, DARKBLUE);
    DrawText(TextFormat("[L: %d]", samurai->stats.lives), SCREEN_WIDTH - 300,
             40, 40, DARKBLUE);
    // ----
    // ----

    // Update and draw timer
    *timer += GetFrameTime();
    DrawText(TextFormat("[T: %.2f]", *timer), 40, 40, 40, DARKBLUE);
    // ----

    // Draw platforms
    for (int i = 0; i < platforms->count; i++) {
        DrawRectangleRec(platforms->units[i].rect, platforms->units[i].color);
        if (DEBUG_RAYLIB)
            DrawRectangleLinesEx(platforms->units[i].rect, 2, WHITE);
    }
    // ----

    // Draw fires
    for (int i = 0; i < fires->count; i++) {
        DrawRectangleRec(fires->units[i].rect, fires->units[i].color);
        if (DEBUG_RAYLIB)
            DrawRectangleLinesEx(fires->units[i].rect, 2, WHITE);
    }
    // ----

    // Draw npcs
    for (int i = 0; i < npcs->count; i++) {
        DrawRectangleRec(npcs->units[i].rect, npcs->units[i].color);
        if (DEBUG_RAYLIB)
            DrawRectangleLinesEx(npcs->units[i].rect, 2, RED);
    }
    // ----

    // Draw portal
    // DrawRectangleRec(portal->rect, portal->color);
    //DrawTexture(portal->animation.texture, portal->rec.x, portal->rec.y, WHITE);
    renderPortal(portal);
    if (DEBUG_RAYLIB)
        DrawRectangleLinesEx(portal->rec, 2, PINK);
    // ----

    // Draw player
    renderSamurai(samurai);
    if (DEBUG_RAYLIB) {
        DrawRectangleLinesEx(samurai->hitbox.rec, 2, RED);
        DrawRectangleLinesEx(samurai->hitbox.slimRec, 2, ORANGE);
        Rectangle samuraiSlashRect = {
            samurai->slash.position.x, samurai->slash.position.y,
            samurai->slash.width, samurai->slash.height};
        if (samurai->slash.isActive) {
            DrawRectangleLinesEx(samuraiSlashRect, 2, YELLOW);
        }
    }
    // ----
}

void renderMenu(Samurai *samurai) {
    // Create samurai instance for menu specific
    Samurai menuSamurai = {
        .position = {SCREEN_WIDTH / 2.0f - SAMURAI_FRAME_SIZE / 2.0f,
                     SCREEN_HEIGHT / 2.0f - SAMURAI_FRAME_SIZE / 2.0f},
        .hitbox = {{}, {}},
        .speed = {8.0f, 0.0f},
        .stats = {3, 100.0f, 20.0f, -20.0f, 1.2f},
        .state = {false, false, false, false, false, false, false},
        .animation = {.frameIndex = 0,
                      .frameCounter = 0.0f,
                      .attackFrame = 0,
                      .assets = {samurai->animation.assets.idleTexture,
                                 samurai->animation.assets.runTexture,
                                 samurai->animation.assets.attackTexture,
                                 samurai->animation.assets.hurtTexture}},
        .slash = {{0, 0}, 0.0f, 0.0f, 0, false}};
    // ----

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

void renderSamurai(Samurai *samurai) {
    Rectangle sourceRect = {
        samurai->animation.frameIndex * SAMURAI_FRAME_SIZE, 0,
        samurai->state.facingLeft ? -SAMURAI_FRAME_SIZE : SAMURAI_FRAME_SIZE,
        SAMURAI_FRAME_SIZE};
    Rectangle destRect = {samurai->position.x, samurai->position.y,
                          SAMURAI_FRAME_SIZE, SAMURAI_FRAME_SIZE};

    Texture2D texture;
    if (samurai->state.isHurt) {
        texture = samurai->animation.assets.hurtTexture;
    } else if (samurai->state.isAttacking) {
        texture = samurai->animation.assets.attackTexture;
    } else if (samurai->state.isRunning) {
        texture = samurai->animation.assets.runTexture;
    } else {
        texture = samurai->animation.assets.idleTexture;
    }

    DrawTexturePro(texture, sourceRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
}

void renderPortal(Portal *portal) {
    int frameWidth = portal->animation.texture.width / PORTAL_FRAME_COUNT;
    Rectangle sourceRect = {portal->animation.currentFrame * frameWidth, 0,
                            frameWidth, portal->animation.texture.height};
    Rectangle destRect = {portal->rec.x, portal->rec.y, portal->rec.width,
                          portal->rec.height};
    DrawTexturePro(portal->animation.texture, sourceRect, destRect,
                   (Vector2){0, 0}, 0.0f, WHITE);
}
