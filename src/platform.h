#ifndef PLATFORM_H
#define PLATFORM_H

#include "config.h"
#include "raylib.h"

typedef struct Platform {
    Rectangle rect;
    Color color;
} Platform;

typedef struct Platforms {
    Platform units[MAX_PLATFORMS];
    int count;
} Platforms;

void newPlatform(Platforms *platforms, int x, int y, int width, int height, Color color);
void resetPlatforms(Platforms *platforms);

void platformsLevel0(Platforms *platforms);
void platformsLevel1(Platforms *platforms);

#endif // PLATFORM_H
