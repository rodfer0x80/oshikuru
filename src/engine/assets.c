#include "engine/assets.h"

// Utils
Texture2D loadTexture(char *textureFilename, int frameCount, int frameSize) {
    Image textureImage = LoadImage(textureFilename);
    if (textureImage.data == NULL) {
        TraceLog(LOG_ERROR,
                 TextFormat("Failed to load asset: '%s'", textureFilename));
        return (Texture2D){0};
    }
    ImageResize(&textureImage, frameCount * frameSize, frameSize);
    Texture2D texture = LoadTextureFromImage(textureImage);
    UnloadImage(textureImage);
    return texture;
}
// --

// Samurai
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

Texture2D loadSamuraiHurtTexture() {
    return loadTexture(SAMURAI_HURT_TEXTURE, SAMURAI_HURT_FRAME_COUNT,
                       SAMURAI_FRAME_SIZE);
}
// --

// NPC
Texture2D loadNPCIdleTexture() {
    return loadTexture(NPC_IDLE_TEXTURE, NPC_IDLE_FRAME_COUNT, NPC_FRAME_SIZE);
}

Texture2D loadNPCAttackTexture() {
    return loadTexture(NPC_ATTACK_TEXTURE, NPC_ATTACK_FRAME_COUNT, NPC_FRAME_SIZE);
}

Texture2D loadNPCHurtTexture() {
    return loadTexture(NPC_HURT_TEXTURE, NPC_HURT_FRAME_COUNT, NPC_FRAME_SIZE);
}

Texture2D loadNPCDeathTexture() {
    return loadTexture(NPC_DEATH_TEXTURE, NPC_DEATH_FRAME_COUNT, NPC_FRAME_SIZE);
}

Texture2D loadNPCFlyingTexture() {
    return loadTexture(NPC_FLYING_TEXTURE, NPC_FLYING_FRAME_COUNT, NPC_FRAME_SIZE);
}

Texture2D loadNPCProjectileTexture() {
    return loadTexture(NPC_PROJECTILE_TEXTURE, NPC_PROJECTILE_FRAME_COUNT, NPC_FRAME_SIZE);
}
// --

// Portal
Texture2D loadPortalTexture() {
    return loadTexture(PORTAL_TEXTURE, PORTAL_FRAME_COUNT, PORTAL_FRAME_SIZE);
}
// --