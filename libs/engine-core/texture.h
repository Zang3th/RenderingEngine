#ifndef TEXTURE
#define TEXTURE

#include "../../vendor/image/stb_image.h"
#include "engine-core/errorManager.h"
#include "../../vendor/logging/log.h"

//--- Functions ---
unsigned int* createTexture(const char* path);
void deleteTexture(unsigned int* textureID);
void bindTexture(const unsigned int* textureID);
void unbindTexture();

#endif