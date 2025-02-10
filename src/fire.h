#ifndef FIRE_H
#define FIRE_H

#include "config.h"
#include "raylib.h"

typedef struct Fire {
    Rectangle rect;
    Color color;
    int damage;
} Fire;

typedef struct Fires {
    Fire units[MAX_FIRES];
    int count;
} Fires;

void newFire(Fires *fires, int x, int y, int width, int height, Color color,
             int damage);
void resetFires(Fires *fires);

void firesLevel0(Fires *fires);
void firesLevel1(Fires *fires);

#endif // FIRE_H
