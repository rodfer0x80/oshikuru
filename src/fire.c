#include "fire.h"
#include "config.h"
#include "string.h"

void newFire(Fires *fires, int x, int y, int width, int height, Color color,
             int damage) {
    if (fires->count < MAX_FIRES) {
        fires->units[fires->count] =
            (Fire){(Rectangle){x, y, width, height}, color, damage};
        fires->count++;
    }
}

void resetFires(Fires *fires) {
    fires->count = 0;
    memset(fires->units, 0, MAX_FIRES * sizeof(fires->units));
}

void firesLevel0(Fires *fires) {
    resetFires(fires);
    newFire(fires, 200, 350-20, 100, 20, ORANGE, 10);
    newFire(fires, 400, 350-20, 100, 20, ORANGE, 10);
}

void firesLevel1(Fires *fires) {
    resetFires(fires);
    newFire(fires, 0, SCREEN_HEIGHT-20, SCREEN_WIDTH, 20, ORANGE, 2);
}
