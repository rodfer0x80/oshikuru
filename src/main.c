#include "raylib.h"
#include "resource_dir.h"

#include "config.h"
#include "game.h"
#include "resources.h"
#include "samurai.h"
#include "platform.h"

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

    // State data
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
        false                                         // isDead
    };
    platformLevel0();    
    bool inGame = false;
    // ----

    // Main loop
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER) && !samurai.isDead) {
            inGame = !inGame;
        }

        if (inGame) {
            updateSamurai(&samurai);
        }

        BeginDrawing();
        if (samurai.isDead) {
            inGame = false;
            renderEndgame();
        } else {
            if (inGame) {
                renderGame(&samurai);
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
    CloseWindow();
    return 0;
    // ----
}
