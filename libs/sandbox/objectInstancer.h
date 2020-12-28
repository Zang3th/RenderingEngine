#ifndef OBJECTINSTANCER
#define OBJECTINSTANCER

#include "../engine-core/resourceManager.h"
#include <cglm/cglm.h>
#include "../engine-core/physicsEngine.h"

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
    float width;
    float height;
    float mass;
} instance_t;

static unsigned int instanceID = 0;

// --- Functions ---
instance_t* objectInstancerCreateInstance(unsigned int* texture, float* color, float size, float mass);
void objectInstancerAddInstance(instance_t* instance, float* position);
void objectInstancerSetWorldtransform(instance_t* instance);
void objectInstancerDeletePhysicsInstance(instance_t* instance);
void objectInstancerDeleteInstance(instance_t* instance);

#endif