#ifndef PLATFORM_H
#define PLATFORM_H

#include "config.h"
#include "raylib.h"

typedef struct Platform {
    Rectangle rect;
    Color color;
} Platform;

extern Platform platforms[MAX_PLATFORMS];
extern int platformCount;

void platformLevel0();

#endif // PLATFORM_H
