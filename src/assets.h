#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

Texture2D loadTexture(char* textureFilePath, int frameCount, int frameSize);
Texture2D loadSamuraiIdleTexture();
Texture2D loadSamuraiRunTexture();
Texture2D loadSamuraiAttackTexture();
Texture2D loadSamuraiHurtTexture();

#endif // ASSETS_H
