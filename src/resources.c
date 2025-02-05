#include <stddef.h>

#include "raylib.h"

#include "config.h"
#include "resources.h"

Texture2D loadSamuraiIdleTexture() {
  Image samuraiIdleImage = LoadImage("samurai_idle.png");
  if (samuraiIdleImage.data == NULL) {
    TraceLog(LOG_ERROR, "Failed to load resource: 'samurai_idle.png'");
    return (Texture2D){0};
  }
  ImageResize(&samuraiIdleImage, SAMURAI_FRAME_COUNT * SAMURAI_FRAME_SIZE,
              SAMURAI_FRAME_SIZE);
  Texture2D samuraiIdleTexture = LoadTextureFromImage(samuraiIdleImage);
  UnloadImage(samuraiIdleImage);
  return samuraiIdleTexture;
}
