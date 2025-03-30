#include "raylib.h"

#include "config.h"
#include "engine/assets.h"
#include "engine/render.h"
#include "entities/npc.h"
#include "entities/samurai.h"
#include "utils/resource_dir.h"
#include "world/fire.h"
#include "world/platform.h"
#include "world/portal.h"

void runLevel(int *level, float *timer, bool *nextLevel, Samurai *samurai,
              Platforms *platforms, Fires *fires, NPCS *npcs,
              NPCAssets NPCLoadedAssets, Portal *portal) {
    *timer = 0.0f;
    *nextLevel = false;
    samurai->position.x = SCREEN_WIDTH;
    samurai->position.y = SCREEN_HEIGHT;
    samurai->state.facingLeft = true;
    samurai->stats.hitpoints = 100.0f;
    if (*level == 0) {
        platformsLevel0(platforms);
        firesLevel0(fires);
        portalLevel0(portal);
        npcsLevel0(npcs, NPCLoadedAssets);
    }
    if (*level == 1) {
        platformsLevel1(platforms);
        firesLevel1(fires);
        portalLevel1(portal);
        npcsLevel1(npcs, NPCLoadedAssets);
    }
    TraceLog(LOG_INFO, TextFormat("[MAIN]: Level %d started", *level));
}

int main() {
    // Init and configs
    SearchAndSetResourceDir("resources");
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetTargetFPS(FPS);
    TraceLog(LOG_INFO, TextFormat("[MAIN]: Rendering window as (%d,%d)",
                                  SCREEN_WIDTH, SCREEN_HEIGHT));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OSHIKURU");
    // ----

    // Load assets
    // TODO: move this and the cleanup to functions in render
    Texture2D samuraiIdleTexture = loadSamuraiIdleTexture();
    Texture2D samuraiRunTexture = loadSamuraiRunTexture();
    Texture2D samuraiAttackTexture = loadSamuraiAttackTexture();
    Texture2D samuraiHurtTexture = loadSamuraiHurtTexture();
    Texture2D portalTexture = loadPortalTexture();
    Texture2D NPCIdleTexture = loadNPCIdleTexture();
    Texture2D NPCAttackTexture = loadNPCAttackTexture();
    Texture2D NPCHurtTexture = loadNPCHurtTexture();
    Texture2D NPCDeathTexture = loadNPCDeathTexture();
    Texture2D NPCFlyingTexture = loadNPCFlyingTexture();
    Texture2D NPCProjectileTexture = loadNPCProjectileTexture();
    NPCAssets NPCLoadedAssets = {.idleTexture = NPCIdleTexture,
                                 .attackTexture = NPCAttackTexture,
                                 .hurtTexture = NPCHurtTexture,
                                 .deathTexture = NPCDeathTexture,
                                 .flyingTexture = NPCFlyingTexture,
                                 .projectileTexture = NPCProjectileTexture};
    // ----

    // Game data
    Samurai samurai = {
        .position = {SCREEN_WIDTH, SCREEN_HEIGHT},
        .speed = {8.0f, 0.0f},
        .hitbox = {{}, {}},
        .stats = {3, 100.0f, 20.0f, -20.0f, 1.2f},
        .state = {true, false, false, false, false, false, false},
        .animation = {.frameIndex = 0,
                      .frameCounter = 0.0f,
                      .attackFrame = 0,
                      .assets = {samuraiIdleTexture, samuraiRunTexture,
                                 samuraiAttackTexture, samuraiHurtTexture}},
        .slash = {{0, 0}, 0.0f, 0.0f, 0.0f, false}};
    Platforms platforms = {{}, 0};
    Fires fires = {{}, 0};
    NPCS npcs = {{}, 0};
    Portal portal = {
        .rec = {}, .color = 0, .animation = {portalTexture, 0, 0.0f}};
    bool inGame = false;
    int level = 0;
    bool nextLevel = true;
    float timer = 0.0;
    // ----

    // Main loop
    float deltaTime;
    while (!WindowShouldClose()) {
        deltaTime = GetFrameTime();
        BeginDrawing();

        // Ingame commands
        // Listen for <ENTER> for quit or menu
        if (IsKeyPressed(KEY_ENTER) && !samurai.state.isDead)
            inGame = !inGame;
        // ----

        // Menu condition
        if (!inGame) {
            renderMenu(&samurai);
            EndDrawing();
            continue;
        }
        // ----

        // DEBUG ingame commands
        if (DEBUG_RAYLIB) {
            // Next level
            if (IsKeyPressed(KEY_N)) {
                // MAX_LEVEL + 1 to allow skiping level until victory condition
                if (level + 1 <= MAX_LEVEL + 1) {
                    level++;
                    nextLevel = true;
                }
            }
            // Previous level
            if (IsKeyPressed(KEY_P)) {
                if (level - 1 >= 0) {
                    level--;
                    nextLevel = true;
                }
            }
            // Restart level
            if (IsKeyPressed(KEY_R))
                nextLevel = true;
            // Reborn samurai
            if (IsKeyPressed(KEY_U)) {
                level = 0;
                nextLevel = true;
                samurai.state.isDead = false;
                samurai.stats.lives = 3;
                samurai.stats.hitpoints = 100.0f;
                samurai.position.x = SCREEN_WIDTH;
                samurai.position.y = SCREEN_HEIGHT;
                samurai.state.facingLeft = true;
            }
        }
        // ----

        // Endgame conditions
        // Victory condition
        if (level > MAX_LEVEL) {
            renderVictory();
            EndDrawing();
            continue;
        }
        // ----

        // Defeat condition
        if (samurai.state.isDead) {
            renderDefeat();
            EndDrawing();
            continue;
            // ----
        }
        // ----

        // Update level
        if (nextLevel)
            runLevel(&level, &timer, &nextLevel, &samurai, &platforms, &fires,
                     &npcs, NPCLoadedAssets, &portal);
        // ----

        // Update level on samurai death (if lives > 0)
        if (samurai.state.hasDied) {
            samurai.state.hasDied = false;
            runLevel(&level, &timer, &nextLevel, &samurai, &platforms, &fires,
                     &npcs, NPCLoadedAssets, &portal);
        }
        // ----

        // Update game state
        if (inGame) {
            updateSamurai(&samurai, &platforms, &fires, &npcs, &deltaTime);
            updateNPCS(&npcs, &samurai, &deltaTime);
            updatePortal(&portal, &deltaTime);
            // Next level condition
            if (samuraiPassesPortal(&samurai, &portal)) {
                level++;
                nextLevel = true;
                TraceLog(LOG_INFO,
                         TextFormat("[MAIN]: Portal %d crossed", level));
            }
            // Render game state
            renderGame(&samurai, &platforms, &fires, &portal, &npcs, &timer);
        }
        // ----

        EndDrawing();
    }

    // Cleanup and close
    resetPlatforms(&platforms);
    resetFires(&fires);
    // TODO: (research) unload main texture like idleTexture
    // or samurai pointer is same?
    UnloadTexture(samuraiIdleTexture);
    UnloadTexture(samuraiRunTexture);
    UnloadTexture(samuraiAttackTexture);
    UnloadTexture(samuraiHurtTexture);
    UnloadTexture(NPCIdleTexture);
    UnloadTexture(NPCAttackTexture);
    UnloadTexture(NPCHurtTexture);
    UnloadTexture(NPCDeathTexture);
    UnloadTexture(NPCFlyingTexture);
    CloseWindow();
    // ----

    return 0;
}
