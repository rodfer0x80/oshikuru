#include "raylib.h"
#include "resource_dir.h"

#include "assets.h"
#include "config.h"
#include "fire.h"
#include "game.h"
#include "platform.h"
#include "portal.h"
#include "npc.h"
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
        .position = {SCREEN_WIDTH, SCREEN_HEIGHT},          
        .speed = {8.0f, 0.0f},                              
        .hitbox = {{}, {}},                              
        .stats = {100.0f, 20.0f, -20.0f, 1.2f},                   
        .state = {true, false, false, false, false, false}, 
        .animation =
            {
             .frameIndex = 0,
             .frameCounter = 0.0f,
             .attackFrame = 0,
             .assets = {samuraiIdleTexture, samuraiRunTexture,
                        samuraiAttackTexture, samuraiHurtTexture}},
        .slash = {{0, 0}, 0.0f, 0.0f, 0.0f, false} 
    };
    Platforms platforms = {{}, 0};
    Fires fires = {{}, 0};
    NPCS npcs = {{}, 0};
    Portal portal;
    bool inGame = false;
    int level = 0;
    int nextLevel = true;
    float timer = 0.0;
    // ----

    // Main loop
    while (!WindowShouldClose()) {
        // Listen for <ESQ> or <ENTER> for quit or menu
        if (IsKeyPressed(KEY_ENTER) && !samurai.state.isDead) {
            inGame = !inGame;
        }
        // DEBUG: level jump
        if (DEBUG_RAYLIB) {
            if (IsKeyPressed(KEY_N)) {
                if (level + 1 <= MAX_LEVEL){
                    level++;
                    nextLevel = true;
                }
            }
            if (IsKeyPressed(KEY_P)) {
                if (level - 1 >= 0) {
                    level--;
                    nextLevel = true;
                }
            }
            if (IsKeyPressed(KEY_R)) {
                nextLevel = true;
            }
        }

        // Update level
        if (level == 0 && nextLevel) {
            timer = 0.0;
            nextLevel = false;
            samurai.position.x = SCREEN_WIDTH;
            samurai.position.y = SCREEN_HEIGHT;
            samurai.state.facingLeft = true;
            samurai.stats.hitpoints = 100;
            platformsLevel0(&platforms);
            firesLevel0(&fires);
            portalLevel0(&portal);
            npcsLevel0(&npcs);
        }
        if (level == 1 && nextLevel) {
            timer = 0.0;
            nextLevel = false;
            samurai.position.x = SCREEN_WIDTH;
            samurai.position.y = SCREEN_HEIGHT;
            samurai.state.facingLeft = true;
            samurai.stats.hitpoints = 100;
            platformsLevel1(&platforms);
            firesLevel1(&fires);
            portalLevel1(&portal);
            npcsLevel1(&npcs);
        }
        // Update player
        if (inGame) {
            updateSamurai(&samurai, &platforms, &fires);
            updateNPCS(&npcs, &samurai);
        }
        // ----

        BeginDrawing();
        
        // Game logic
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
                        nextLevel = true;
                    }
                    renderGame(&samurai, &platforms, &fires, &portal, &npcs, &timer);
                }
            } else {
                renderMenu(&samurai);
            }
        }
        // ----

        EndDrawing();
    }
    // ----

    // Cleanup and close
    resetPlatforms(&platforms);
    resetFires(&fires);
    // TODO: (research) unload main texture like idleTexture 
    // or samurai pointer is same?
    UnloadTexture(samurai.animation.assets.idleTexture);
    UnloadTexture(samurai.animation.assets.runTexture);
    UnloadTexture(samurai.animation.assets.attackTexture);
    UnloadTexture(samurai.animation.assets.hurtTexture);
    CloseWindow();
    // ----
    
    return 0;
}
