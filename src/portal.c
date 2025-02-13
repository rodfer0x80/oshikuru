#include "portal.h"

void newPortal(Portal *portal, int x, int y, int width, int height, Color color){
    portal->rect = (Rectangle){x, y, width, height};
    portal->color = color;
}

void portalLevel0(Portal *portal){
    newPortal(portal, 330, 270, 40, 80, BLACK);
}

void portalLevel1(Portal *portal){
    newPortal(portal, 0, SCREEN_HEIGHT - 80, 40, 80, BLACK);
}

