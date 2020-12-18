#ifndef OBJECTINSTANCER
#define OBJECTINSTANCER

#include "../engine-core/resourceManager.h"
#include <cglm/cglm.h>

// --- Variables ---
#define MAX_INSTANCES 100

typedef struct {
    unsigned int instanceID;
    unsigned int instanceAmount;
    unsigned int* vao;
    unsigned int* vboM;
    mat4 modelBuffer[MAX_INSTANCES];
    unsigned int* texture;
    unsigned int* shader;
    vec3 color;
} ObjInstance;

static unsigned int instanceID = 0;

// --- Functions ---
ObjInstance* objectInstancerCreateInstance(unsigned int* texture, float* color);
void objectInstancerAddInstance(ObjInstance* instance, float* position);
void objectInstancerDeleteInstance(ObjInstance* instance);

#endif