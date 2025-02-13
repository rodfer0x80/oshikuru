#include "stddef.h"
#include "string.h"

#include "raylib.h"

#include "config.h"
#include "fire.h"

void newFire(Fires *fires, Vector2 *position, int width, int height,
             Color color, int damage) {
    if (fires->count < MAX_FIRES) {
        fires->units[fires->count] =
            (Fire){(Rectangle){position->x, position->y, width, height}, color,
                   damage};
        fires->count++;
    } else {
        TraceLog(LOG_ERROR, TextFormat("[Error] %s:%d -> "
                                       "Max number reached: %d == %d " __FILE__,
                                       __LINE__, fires->count, MAX_FIRES));
    }
}

void resetFires(Fires *fires) {
    fires->count = 0;
    memset(fires->units, 0, MAX_FIRES * sizeof(Fire));
}

void firesLevel0(Fires *fires) {
    int fireWidth = 100;
    int fireHeight = 20;
    Vector2 fire1Position = {200, 350 - fireHeight};
    Vector2 fire2Position = {400, 350 - fireHeight};
    Color fireColor = ORANGE;
    int fireDamage = 10;

    resetFires(fires);

    newFire(fires, &fire1Position, fireWidth, fireHeight, fireColor,
            fireDamage);
    newFire(fires, &fire2Position, fireWidth, fireHeight, fireColor,
            fireDamage);
}

void firesLevel1(Fires *fires) {
    int fireWidth = SCREEN_WIDTH;
    int fireHeight = 20;
    Vector2 fire1Position = {0, SCREEN_HEIGHT - fireHeight};
    Color fireColor = ORANGE;
    int fireDamage = 2;

    resetFires(fires);

    newFire(fires, &fire1Position, fireWidth, fireHeight, fireColor,
            fireDamage);
}
