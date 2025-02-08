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
    newPlatform(0, SCREEN_HEIGHT - 8, SCREEN_WIDTH, 8, BLACK);
    newPlatform(700, 550, 50, 8, BROWN);
    newPlatform(200, 400, 300, 8, YELLOW);
    newPlatform(600, 300, 200, 8, GREEN);
    newPlatform(600, 700, 200, 8, PURPLE);
}

void platformLevel1() {
    resetPlatforms();
    newPlatform(0, SCREEN_HEIGHT - 8, SCREEN_WIDTH, 8, BLACK);
}
