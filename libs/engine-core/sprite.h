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
} Sprite;

// --- Functions ---
unsigned int* createVertexData();
Sprite* createSprite(unsigned int* vertexData, unsigned int* texture, unsigned int* shader, float* basePosition, float* baseSize, float baseRotation, float* baseColor, bool clickable);
void translateSprite(Sprite* sprite, float* position);
void deleteSprite(Sprite* sprite);
void deleteVertexData(unsigned int* vertexData);

#endif