#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include "../engine-core/general/pixelRenderer.h"
#include "../engine-core/2D/window2D.h"
#include "ui_powderTrain.h"
#include "../engine-core/general/random.h"

#define SAND_INDEX 1
#define WATER_INDEX 2

// --- Variables ---
static vec3 colorLookUp[3] = 
{
    (vec3){1.0f, 1.0f, 1.0f},       //Placeholder
    (vec3){0.839f, 0.749f, 0.4f},   //Sand
    (vec3){0.286f, 0.607f, 0.933f}  //Water
};
static int moveFactorLookUp[3] = {
    0,                              //Placeholder
    50,                             //Sand
    50                              //Water
};
static int particleArray[CANVAS_HEIGHT][CANVAS_WIDTH][2];

// --- Functions ---
void particleSystemInit();
void particleSystemCheckSpawn();
void particleSystemUpdate();
void particleSystemCleanUp();

#endif