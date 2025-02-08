#include "platform.h"
#include "config.h"
#include "string.h"

Platform platforms[MAX_PLATFORMS];
int platformCount = 0;

void newPlatform(int x, int y, int width, int height, Color color) {
    if (platformCount < MAX_PLATFORMS) {
        platforms[platformCount] =
            (Platform){(Rectangle){x, y, width, height}, color};
        platformCount++;
    }
}

void resetPlatforms() {
    platformCount = 0;
    memset(platforms, 0, MAX_PLATFORMS * sizeof(Platform));
}

void platformLevel0() {
    resetPlatforms();
    newPlatform(0, SCREEN_HEIGHT - 12, SCREEN_WIDTH, 12, DARKBLUE);
    newPlatform(700, 550, 50, 12, BROWN);
    newPlatform(200, 400, 300, 12, YELLOW);
    newPlatform(600, 300, 200, 12, GREEN);
    newPlatform(600, 700, 200, 12, PURPLE);
}

void platformLevel1() {
    resetPlatforms();
    newPlatform(0, SCREEN_HEIGHT - 12, SCREEN_WIDTH, 12, BLACK);
}
