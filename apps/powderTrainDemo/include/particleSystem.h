#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include "../../../engine-core/general/include/pixelRenderer.h"
#include "../../../engine-core/2D/include/window2D.h"
#include "ui_powderTrain.h"
#include "../../../engine-core/general/include/random.h"

#define SAND_INDEX 1
#define WATER_INDEX 2
#define STONE_INDEX 3
#define FIRE_INDEX 4
#define ACID_INDEX 5
#define WOOD_INDEX 6

// --- Variables ---
static vec3 colorLookUp[7] = 
{
    (vec3){1.0f, 1.0f, 1.0f},       //Placeholder
    (vec3){0.839f, 0.749f, 0.4f},   //Sand
    (vec3){0.286f, 0.607f, 0.933f}, //Water
    (vec3){0.541f, 0.541f, 0.541f}, //Stone
    (vec3){0.941f, 0.094f, 0.0f},   //Fire
    (vec3){0.007f, 0.968f, 0.027f}, //Acid
    (vec3){0.352f, 0.247f, 0.168f}  //Wood
};
static int moveFactorLookUp[7] = {
    0,                              //Placeholder
    50,                             //Sand
    50,                             //Water
    0,                              //Stone
    50,                             //Fire
    50,                             //Acid
    0                               //Wood
};
static bool destroyableCellsLookUp[7] = {
    false,                           //Placeholder
    true,                            //Sand
    true,                            //Water
    false,                           //Stone
    true,                            //Fire
    false,                           //Acid
    true                             //Wood
};
static bool destroyerCellsLookUp[7] = 
{
    false,                           //Placeholder
    false,                           //Sand
    false,                           //Water
    false,                           //Stone
    true,                            //Fire
    true,                            //Acid
    false                            //Wood
};
static int particleArray[CANVAS_HEIGHT][CANVAS_WIDTH][2];

// --- Functions ---
void particleSystemInit();
void particleSystemCheckSpawn();
void particleSystemUpdate();
void particleSystemCleanUp();

#endif