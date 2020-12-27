#ifndef PHYSICSENGINE
#define PHYSICSENGINE

#include <chipmunk/chipmunk.h>
#include <cglm/cglm.h>
#include "../../vendor/logging/log.h"

// --- Variables ---
static cpSpace* space;
static cpShape* groundShape, *boxShape;
static cpBody* boxBody;

extern unsigned int HEIGHT;
extern unsigned int WIDTH;

// --- Functions ---
void physicsEngineInit();
void phyicsEnginePerFrame(float dt);
unsigned int physicsEngineAddBox(float x, float y);
void physicsEngineGetWorldtransform(float* position, float* rotation);
void physicsEngineCleanUp();

#endif