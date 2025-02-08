#ifndef PORTAL_H
#define PORTAL_H

#include "config.h"
#include "raylib.h"

typedef struct Portal {
    Rectangle rect;
    Color color;
} Portal;

extern Portal portal;

void newPortal(int x, int y, int width, int height, Color color);

void portalLevel0();
void portalLevel1();

#endif // PORTAL_H
