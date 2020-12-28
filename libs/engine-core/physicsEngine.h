#ifndef PHYSICSENGINE
#define PHYSICSENGINE

#include <chipmunk/chipmunk.h>
#include <cglm/cglm.h>
#include "../../vendor/logging/log.h"
#include <stdbool.h>

// --- Variables ---
#define MAX_PHYSICS_OBJECTS 200

static cpSpace* space;
static cpShape* groundShape, *leftWallShape, *rightWallShape, *ceilingShape;

extern unsigned int HEIGHT;
extern unsigned int WIDTH;

typedef struct{
    cpShape* boxShape;
    cpBody* boxBody;
    bool slotUsed;
} physicsBox_t;

static physicsBox_t boxes[MAX_PHYSICS_OBJECTS];
static unsigned int physicsObjCounter = 0; 

// --- Functions ---
void physicsEngineInit();
void phyicsEnginePerFrame(float dt);
unsigned int physicsEngineAddBox(unsigned int id, float x, float y, float width, float height, float mass);
void physicsEngineGetWorldtransform(unsigned int id, float* position, float* rotation);
void physicsEngineDeleteObject(unsigned int id);
void physicsEngineDeleteScene();
void physicsEngineCleanUp();

#endif