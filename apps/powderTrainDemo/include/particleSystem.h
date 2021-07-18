#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include "../../../engine-core/general/include/pixelRenderer.h"
#include "../../../engine-core/2D/include/window2D.h"
#include "ui_powderTrain.h"
#include "../../../engine-core/general/include/random.h"

#define SAND_ID 1
#define WATER_ID 2
#define STONE_ID 3
#define FIRE_ID 4
#define ACID_ID 5
#define WOOD_ID 6

// --- Variables ---
typedef struct{
    unsigned int id;
    vec3 color;
    unsigned int moveFactor;
    bool isDestroyable;
    bool isDestroyer;
} particle_t;

static int particleArray[CANVAS_HEIGHT][CANVAS_WIDTH][2];
static particle_t particleLookUp[7];

// --- Functions ---
void particleSystemInit();
void particleSystemCheckSpawn();
void particleSystemUpdate();
void particleSystemCleanUp();

#endif