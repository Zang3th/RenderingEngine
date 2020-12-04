#ifndef SPRITE
#define SPRITE

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "texture.h"
#include <cglm/cglm.h>
#include <stdlib.h>
#include "window.h"

//--- Functions ---
unsigned int* initSpriteData();
void renderSprite(unsigned int* spriteData, unsigned int* texture, unsigned int* shader, vec2 position, vec2 size, float rotation, vec3 color);
void deleteSpriteData(unsigned int* spriteData);

#endif