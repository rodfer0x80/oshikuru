#ifndef PORTAL_H
#define PORTAL_H

#include "stddef.h"

#include "raylib.h"

#include "config.h"

typedef struct PortalAnimation {
    Texture2D texture;
    int currentFrame;
    float frameTime;
} PortalAnimation;

typedef struct Portal {
    Rectangle rec;
    Color color;
    PortalAnimation animation;
} Portal;

void newPortal(Portal *portal, int x, int y, int width, int height,
               Color color);

void updatePortal(Portal *portal, float *deltaTime);

void portalLevel0(Portal *portal);

void portalLevel1(Portal *portal);

#endif // PORTAL_H
