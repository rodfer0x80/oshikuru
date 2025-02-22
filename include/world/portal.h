#ifndef PORTAL_H
#define PORTAL_H

#include "stddef.h"

#include "raylib.h"

#include "config.h"

typedef struct Portal {
    Rectangle rect;
    Color color;
} Portal;

void newPortal(Portal *portal, int x, int y, int width, int height, Color color);

void portalLevel0(Portal *portal);

void portalLevel1(Portal *portal);

#endif // PORTAL_H
