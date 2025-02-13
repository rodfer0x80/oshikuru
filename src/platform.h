#ifndef PLATFORM_H
#define PLATFORM_H

#include "stddef.h"
#include "string.h"

#include "raylib.h"

#include "config.h"

typedef struct Platform {
    Rectangle rect;
    Color color;
} Platform;

typedef struct Platforms {
    Platform units[MAX_PLATFORMS];
    int count;
} Platforms;

void newPlatform(Platforms *platforms, Vector2 position, int width, int height, Color color);

void resetPlatforms(Platforms *platforms);

void platformsLevel0(Platforms *platforms);

void platformsLevel1(Platforms *platforms);

#endif // PLATFORM_H
