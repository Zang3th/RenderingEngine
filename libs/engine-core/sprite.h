#ifndef SPRITE
#define SPRITE

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "texture.h"
#include <cglm/cglm.h>
#include <stdlib.h>

unsigned int* initSpriteData();
void renderSprite(unsigned int* spriteData, unsigned int* texture, unsigned int* shader, vec3 color);
void deleteSpriteData(unsigned int* spriteData);

#endif