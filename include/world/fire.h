#ifndef FIRE_H
#define FIRE_H

#include "stddef.h"
#include "string.h"

#include "raylib.h"

#include "config.h"

typedef struct Fire {
    Rectangle rect;
    Color color;
    int damage;
} Fire;

typedef struct Fires {
    Fire units[MAX_FIRES];
    int count;
} Fires;

void newFire(Fires *fires, Vector2 *position, int width, int height, Color color,
             int damage);

void resetFires(Fires *fires);

void firesLevel0(Fires *fires);

void firesLevel1(Fires *fires);

#endif // FIRE_H
