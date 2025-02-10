#ifndef PORTAL_H
#define PORTAL_H

#include "config.h"
#include "raylib.h"

typedef struct Portal {
    Rectangle rect;
    Color color;
} Portal;

void newPortal(Portal *portal, int x, int y, int width, int height, Color color);

void portalLevel0(Portal *portal);
void portalLevel1(Portal *portal);

#endif // PORTAL_H
