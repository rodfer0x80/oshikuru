#include "stddef.h"
#include "raylib.h"
#include "portal.h"

Portal portal;

void newPortal(int x, int y, int width, int height, Color color){
    portal = (Portal){(Rectangle){x, y, width, height}, color};
}

void portalLevel0(){
    newPortal(SCREEN_WIDTH - 40, SCREEN_HEIGHT - 80, 40, 80, DARKBLUE);
}

void portalLevel1(){
    newPortal(0, SCREEN_HEIGHT - 80, 40, 80, DARKBLUE);
}

