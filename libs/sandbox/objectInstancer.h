#ifndef OBJECTINSTANCER
#define OBJECTINSTANCER

#include "../engine-core/resourceManager.h"
#include <cglm/cglm.h>

// --- Variables ---
#define MAX_INSTANCES 100

unsigned int* blockTexture, *instancedShader; 
unsigned int* vao, *vbo1, *vbo2;
unsigned int currentInstanceCount;
mat4 modelBuffer[1];

// --- Functions ---
void objectInstancerInit();
void objectInstancerAddInstance(float* position);
void objectInstancerRender();

#endif