#include "raylib.h"
#include "resource_dir.h"

#include "config.h"
#include "fire.h"
#include "game.h"
#include "platform.h"
#include "portal.h"
#include "assets.h"
#include "samurai.h"

int main() {
    // Init and configs
    SearchAndSetResourceDir("resources");
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetTargetFPS(FPS);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OSHIKURU");
    // ----

    // Load resources
    Texture2D samuraiIdleTexture = loadSamuraiIdleTexture();
    Texture2D samuraiRunTexture = loadSamuraiRunTexture();
    Texture2D samuraiAttackTexture = loadSamuraiAttackTexture();
    Texture2D samuraiHurtTexture = loadSamuraiHurtTexture();
    if (samuraiIdleTexture.id == 0 || samuraiRunTexture.id == 0 ||
        samuraiAttackTexture.id == 0 || samuraiHurtTexture.id == 0) {
        CloseWindow();
        return -1;
    }
    // ----

    // Game data
    Samurai samurai = {
        .position = {SCREEN_WIDTH,
                     SCREEN_HEIGHT},         // position
        .speed = {8.0f, 0.0f},                               // speed
        .stats = {100, 20, -20.0f, 1.2f},                    // stats
        .state = {true, false, false, false, false, false}, // state
        .animation =
            {// animation
             .frameIndex = 0,
             .frameCounter = 0.0f,
             .attackFrame = 0,
             .assets = {samuraiIdleTexture, samuraiRunTexture,
                        samuraiAttackTexture, samuraiHurtTexture}},
        .slash = {{0, 0}, 0.0f, 0.0f, 0, false} // slash
    };
    Platforms platforms = {{}, 0};
    Fires fires = {{}, 0};
    Portal portal;
    bool inGame = false;
    int level = 0;
    // ----

    // Main loop
    while (!WindowShouldClose()) {
        // Listen for <ESQ> or <ENTER> for quit or menu
        if (IsKeyPressed(KEY_ENTER) && !samurai.state.isDead) {
            inGame = !inGame;
        }

        // Update level
        if (level == 0) {
            platformsLevel0(&platforms);
            firesLevel0(&fires);
            portalLevel0(&portal);
        }
        if (level == 1) {
            platformsLevel1(&platforms);
            firesLevel1(&fires);
            portalLevel1(&portal);
        }
        // Update player
        if (inGame) {
            updateSamurai(&samurai, &platforms, &fires);
        }

        BeginDrawing();

        if (samurai.state.isDead) {
            inGame = false;
            renderDefeat();
        } else {
            if (inGame) {
                if (level > MAX_LEVEL) {
                    renderVictory();
                } else {
                    if (samuraiPassesPortal(&samurai, &portal)) {
                        level++;
                    }
                    if (DEBUG_RAYLIB) {
                        if (IsKeyPressed(KEY_N)) {
                            level++;
                        }
                    }
                    renderGame(&samurai, &platforms, &fires, &portal);
                }
            } else {
                renderMenu(&samurai);
            }
        }

        EndDrawing();
    }
    // ----

    // Cleanup and close
    resetPlatforms(&platforms);
    resetFires(&fires);
    UnloadTexture(samurai.animation.assets.idleTexture);
    UnloadTexture(samurai.animation.assets.runTexture);
    UnloadTexture(samurai.animation.assets.attackTexture);
    UnloadTexture(samurai.animation.assets.hurtTexture);
    CloseWindow();
    return 0;
    // ----
}
