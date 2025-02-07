#include "platform.h"
#include "config.h"

Platform platforms[MAX_PLATFORMS];
int platformCount = 0;

void platformLevel0() {
    platforms[0] = (Platform){
        (Rectangle){0, SCREEN_HEIGHT / 2 + SAMURAI_FRAME_SIZE / 3, SCREEN_WIDTH, 8},
        DARKBLUE
    };
    platformCount++;

    platforms[1] = (Platform){
        (Rectangle){200, 400, 300, 8},
        YELLOW
    };
    platformCount++;

    platforms[2] = (Platform){
        (Rectangle){600, 300, 200, 8},
        GREEN
    };
    platformCount++;
}
