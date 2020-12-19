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
} instance_t;

static unsigned int instanceID = 0;

// --- Functions ---
instance_t* objectInstancerCreateInstance(unsigned int* texture, float* color);
void objectInstancerAddInstance(instance_t* instance, float* position);
void objectInstancerDeleteInstance(instance_t* instance);

#endif