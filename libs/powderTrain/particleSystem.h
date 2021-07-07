#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include "../engine-core/general/pixelRenderer.h"
#include "../engine-core/2D/window2D.h"
#include "ui_powderTrain.h"

// --- Variables ---

// --- Functions ---
void particleSystemInit();
void particleSystemCheckSpawn();
void particleSystemUpdate();
void particleSystemCleanUp();

#endif