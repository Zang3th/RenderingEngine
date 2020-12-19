#ifndef SPRITE
#define SPRITE

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "texture.h"
#include <cglm/cglm.h>
#include <stdlib.h>
#include "window.h"
#include <stdbool.h> 
#include <string.h>

// --- Variables ---
typedef struct{
    unsigned int* vertexData;
    unsigned int* texture;
    unsigned int* shader;
    vec2 basePosition;
    vec2 baseSize;
    float baseRotation;
    vec3 baseColor;
    vec3 currentColor;    
    bool isClickable;
    bool gotClicked;  
    mat4 model;  
} sprite_t;

// --- Functions ---
unsigned int* createVertexData();
sprite_t* createSprite(unsigned int* vertexData, unsigned int* texture, unsigned int* shader, float* basePosition, float* baseSize, float baseRotation, float* baseColor, bool clickable);
void translateSprite(sprite_t* sprite, float* position);
void deleteSprite(sprite_t* sprite);
void deleteVertexData(unsigned int* vertexData);

#endif