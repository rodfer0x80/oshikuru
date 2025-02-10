#include "raylib.h"
#include "resource_dir.h"

#include "config.h"
#include "game.h"
#include "platform.h"
#include "portal.h"
#include "resources.h"
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
        {SCREEN_WIDTH / 2 - SAMURAI_FRAME_SIZE / 2,
         SCREEN_HEIGHT / 2 - SAMURAI_FRAME_SIZE / 2}, // position
        8.0f,                                         // xSpeed
        0.0f,                                         // ySpeed
        100,                                          // hitpoints
        -20.0f,                                       // jumpStrength
        1.2f,                                         // gravityEffect
        samuraiIdleTexture,                           // idleTexture
        samuraiRunTexture,                            // runTexture
        samuraiAttackTexture,                         // attackTexture
        0,                                            // frameIndex
        0.0f,                                         // frameCounter
        false,                                        // facingLeft
        false,                                        // isRunning
        false,                                        // isJumping
        false,                                        // isAttacking
        false,                                        // isHurt
        false,                                        // isDead
        20,                                           // damage
        0,                                           // attackTimer
    };

    Platforms platforms = {
        {},
        0
    };

    Portal portal;

    bool inGame = false;
    int level = 0;
    // ----

    // Main loop
    while (!WindowShouldClose()) {
        // Listen for <ESQ> or <ENTER> for quit or menu
        if (IsKeyPressed(KEY_ENTER) && !samurai.isDead) {
            inGame = !inGame;
        }

        // Update level
        if (level == 0) {
            platformsLevel0(&platforms);
            portalLevel0(&portal);
        }
        if (level == 1) {
            platformsLevel1(&platforms);
            portalLevel1(&portal);
        }
        // Update player
        if (inGame) {
            updateSamurai(&samurai, &platforms);
        }

        BeginDrawing();

        if (samurai.isDead) {
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
                    renderGame(&samurai, &platforms, &portal);
                }
            } else {
                renderMenu(&samurai);
            }
        }

        EndDrawing();
    }
    // ----

    // Cleanup and close
    UnloadTexture(samurai.idleTexture);
    UnloadTexture(samurai.runTexture);
    UnloadTexture(samurai.attackTexture);
    UnloadTexture(samurai.hurtTexture);
    CloseWindow();
    return 0;
    // ----
}
