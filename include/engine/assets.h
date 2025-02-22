#ifndef ASSETS_H
#define ASSETS_H

#include "stddef.h"

#include "raylib.h"

#include "config.h"

Texture2D loadTexture(char* textureFilePath, int frameCount, int frameSize);

Texture2D loadSamuraiIdleTexture();
Texture2D loadSamuraiRunTexture();
Texture2D loadSamuraiAttackTexture();
Texture2D loadSamuraiHurtTexture();

Texture2D loadPortalTexture();

#endif // ASSETS_H
