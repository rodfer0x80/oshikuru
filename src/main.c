#include "raylib.h"
#include "resource_dir.h"

#include "config.h"
#include "game.h"
#include "samurai.h"
#include "resources.h"

int main() {
    SearchAndSetResourceDir("resources");
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetTargetFPS(FPS);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OSHIKURU");

    Texture2D samuraiIdleTexture = loadSamuraiIdleTexture();
    if (samuraiIdleTexture.id == 0) {
        CloseWindow();
        return -1;
    }

    Samurai samurai = {
        {SCREEN_WIDTH / 2 - SAMURAI_FRAME_SIZE / 2,
         SCREEN_HEIGHT / 2 - SAMURAI_FRAME_SIZE / 2}, // position
        8.0f,   // xSpeed - increased for better feel
        0.0f,   // ySpeed
        false,  // isJumping
        -20.0f, // jumpStrength - adjusted for height
        1.2f,   // gravityEffect - adjusted for weight
        samuraiIdleTexture,
        0,    // frameIndex
        true, // facingRight
        0.0f  // frameCounter
    };

    bool inGame = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) {
            inGame = !inGame;
        }

        if (inGame) {
            updateSamurai(&samurai);
        }

        BeginDrawing();
        if (inGame) {
            renderGame(&samurai);
        } else {
            renderMenu(&samurai);
        }
        EndDrawing();
    }

    UnloadTexture(samurai.idleTexture);
    CloseWindow();
    return 0;
}
