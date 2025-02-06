#include <stddef.h>

#include "raylib.h"

#include "config.h"
#include "resources.h"

Texture2D loadTexture(char *textureFilename, int frameCount, int frameSize) {
    Image textureImage = LoadImage(textureFilename);
    if (textureImage.data == NULL) {
        TraceLog(LOG_ERROR,
                 TextFormat("Failed to load resource: '%s'", textureFilename));
        return (Texture2D){0};
    }
    ImageResize(&textureImage, frameCount * frameSize, frameSize);
    Texture2D texture = LoadTextureFromImage(textureImage);
    UnloadImage(textureImage);
    return texture;
}

Texture2D loadSamuraiIdleTexture() {
    return loadTexture(SAMURAI_IDLE_TEXTURE, SAMURAI_IDLE_FRAME_COUNT,
                       SAMURAI_FRAME_SIZE);
}

Texture2D loadSamuraiRunTexture() {
    return loadTexture(SAMURAI_RUN_TEXTURE, SAMURAI_RUN_FRAME_COUNT,
                       SAMURAI_FRAME_SIZE);
}

Texture2D loadSamuraiAttackTexture() {
    return loadTexture(SAMURAI_ATTACK_TEXTURE, SAMURAI_ATTACK_FRAME_COUNT,
                       SAMURAI_FRAME_SIZE);
}
