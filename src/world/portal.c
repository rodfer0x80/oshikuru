#include "world/portal.h"

void newPortal(Portal *portal, int x, int y, int width, int height,
               Color color) {
    portal->rec = (Rectangle){x, y, width, height};
    portal->color = color;
    portal->animation.currentFrame = 0;
    portal->animation.frameTime = 0;
}

void updatePortal(Portal *portal, float *deltaTime) {
    portal->animation.frameTime += *deltaTime;
    if (portal->animation.frameTime >= (1.0f / PORTAL_ANIMATION_SPEED)) {
        portal->animation.frameTime = 0;
        portal->animation.currentFrame =
            (portal->animation.currentFrame + 1) % PORTAL_FRAME_COUNT;
    }
}

void portalLevel0(Portal *portal) {
    newPortal(portal, 310, 260, 80, 100, BLACK);
}

void portalLevel1(Portal *portal) {
    newPortal(portal, 0, SCREEN_HEIGHT - 100, 80, 100, BLACK);
}
