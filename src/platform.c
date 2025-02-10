#include "platform.h"
#include "config.h"
#include "string.h"

void newPlatform(Platforms *platforms, int x, int y, int width, int height, Color color) {
    if (platforms->count < MAX_PLATFORMS) {
        platforms->units[platforms->count] =
            (Platform){(Rectangle){x, y, width, height}, color};
        platforms->count++;
    }
}

void resetPlatforms(Platforms *platforms) {
    platforms->count = 0;
    memset(platforms->units, 0, MAX_PLATFORMS * sizeof(platforms->units));
}

void platformsLevel0(Platforms *platforms) {
    resetPlatforms(platforms);
    newPlatform(platforms, 0, SCREEN_HEIGHT - 16, SCREEN_WIDTH, 16, DARKBLUE);
    newPlatform(platforms, 700, 550, 50, 16, BROWN);
    newPlatform(platforms, 200, 400, 300, 16, YELLOW);
    newPlatform(platforms, 600, 300, 200, 16, GREEN);
    newPlatform(platforms, 600, 700, 200, 16, PURPLE);
}

void platformsLevel1(Platforms *platforms) {
    resetPlatforms(platforms);
    newPlatform(platforms, 0, SCREEN_HEIGHT - 16, SCREEN_WIDTH, 16, DARKBLUE);
}
