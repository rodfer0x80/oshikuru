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

void newPlatform(int x, int y, int width, int height, Color color);
void resetPlatforms();

void platformLevel0();
void platformLevel1();

#endif // PLATFORM_H
