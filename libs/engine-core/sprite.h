#ifndef SPRITE
#define SPRITE

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "texture.h"
#include <cglm/cglm.h>
#include <stdlib.h>
#include "window.h"

// --- Variables ---
typedef struct{
    unsigned int* vertexData;
    unsigned int* texture;
    unsigned int* shader;
    vec2 position;
    vec2 size;
    float rotation;
    vec3 color;
} Sprite;

// --- Functions ---
unsigned int* createVertexData();
Sprite* createSprite(unsigned int* vertexData, unsigned int* texture, unsigned int* shader, float* position, float* size, float rotation, float* color);
void testSprite(Sprite* sprite);
void renderSprite(Sprite* sprite);
void deleteSprite(Sprite* sprite);
void deleteVertexData(unsigned int* vertexData);

#endif