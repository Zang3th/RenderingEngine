#ifndef TEXTURE
#define TEXTURE

#include "../../vendor/include/stb_image.h"
#include "errorManager.h"
#include "../../vendor/include/log.h"

// --- Functions ---
unsigned int createTexture(const char* path);
void deleteTexture(unsigned int textureID);
void bindTexture(unsigned int textureID);
void bindTextureToSlot(unsigned int textureID, unsigned int slot);
void unbindTexture();

#endif