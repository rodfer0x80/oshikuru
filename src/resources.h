#ifndef RESOURCES_H
#define RESOURCES_H

#include "raylib.h"

Texture2D loadTexture(char* textureFilePath, int frameCount, int frameSize);
Texture2D loadSamuraiIdleTexture();
Texture2D loadSamuraiRunTexture();
Texture2D loadSamuraiAttackTexture();

#endif // RESOURCES_H
