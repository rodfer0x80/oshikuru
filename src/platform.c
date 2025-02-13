#include "platform.h"

void newPlatform(Platforms *platforms, Vector2 position, int width, int height,
                 Color color) {
    if (platforms->count < MAX_PLATFORMS) {
        platforms->units[platforms->count] = (Platform){
            (Rectangle){position.x, position.y, width, height}, color};
        platforms->count++;
    } else {
        TraceLog(LOG_ERROR, TextFormat("[Error] %s:%d: -> "
                                       "Max number reached: %d == %d " __FILE__,
                                       __LINE__, platforms->count, MAX_FIRES));
    }
}

void resetPlatforms(Platforms *platforms) {
    platforms->count = 0;
    memset(platforms->units, 0, MAX_PLATFORMS * sizeof(Platform));
}

void platformsLevel0(Platforms *platforms) {
    int platformHeight = 16;
    Vector2 groundPlatformPosition = {0, SCREEN_HEIGHT - platformHeight};
    Vector2 platform1Position = {900, 700};
    Vector2 platform2Position = {700, 450};
    Vector2 platform3Position = {200, 350};
    Vector2 platform4Position = {800, 350};
    Vector2 platform5Position = {600, 600};
    Vector2 platform6Position = {600, 200};

    resetPlatforms(platforms);

    newPlatform(platforms, groundPlatformPosition, SCREEN_WIDTH, platformHeight,
                DARKBLUE);
    newPlatform(platforms, platform1Position, 100, platformHeight, BLUE);
    newPlatform(platforms, platform2Position, 100, platformHeight, BROWN);
    newPlatform(platforms, platform3Position, 300, platformHeight, YELLOW);
    newPlatform(platforms, platform4Position, 300, platformHeight, YELLOW);
    newPlatform(platforms, platform5Position, 200, platformHeight, PURPLE);
    newPlatform(platforms, platform6Position, 200, platformHeight, GREEN);
}

void platformsLevel1(Platforms *platforms) {
    int platformHeight = 16;
    Vector2 groundPlatformPosition = {0, SCREEN_HEIGHT - platformHeight};

    resetPlatforms(platforms);

    newPlatform(platforms, groundPlatformPosition, SCREEN_WIDTH, platformHeight,
                DARKBLUE);
}
