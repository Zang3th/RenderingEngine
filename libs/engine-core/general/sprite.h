#ifndef SPRITE
#define SPRITE

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "texture.h"
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

// --- Variables ---
typedef struct{
    unsigned int* vao;
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
unsigned int* createSpriteVAO();
sprite_t* createSprite(unsigned int* vao, unsigned int* texture, unsigned int* shader, float* basePosition, float* baseSize, float baseRotation, float* baseColor, bool clickable);
void translateSprite(sprite_t* sprite, float* position);
void deleteSprite(sprite_t* sprite);

#endif