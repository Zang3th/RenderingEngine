#ifndef SPRITE
#define SPRITE

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "texture.h"
#include <cglm/cglm.h>
#include <stdlib.h>

typedef struct{
    vec2 position;
    vec2 size;
    float rotation;
    vec3 color;
} Sprite;

unsigned int* initSpriteData();
void renderSprite(unsigned int* spriteData, unsigned int* texture, unsigned int* shader, Sprite* spriteStruct);
void deleteSpriteData(unsigned int* spriteData);

#endif