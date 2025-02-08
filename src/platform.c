#include "platform.h"
#include "config.h"

Platform platforms[MAX_PLATFORMS];
int platformCount = 0;

void platformLevel0() {
    platforms[0] = (Platform){
        (Rectangle){0, SCREEN_HEIGHT-8, SCREEN_WIDTH, 8},
        BLACK
    };
    platformCount++;
    
    platforms[1] = (Platform){
        (Rectangle){700, 550, 50, 8},
        BROWN
    };
    platformCount++;

    platforms[2] = (Platform){
        (Rectangle){200, 400, 300, 8},
        YELLOW
    };
    platformCount++;

    platforms[3] = (Platform){
        (Rectangle){600, 300, 200, 8},
        GREEN
    };
    platformCount++;
    
    platforms[4] = (Platform){
        (Rectangle){600, 700, 200, 8},
        GREEN
    };
    platformCount++;
}
