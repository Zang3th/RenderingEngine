#ifndef OBJECTMANAGER
#define OBJECTMANAGER

#include "ui.h"
#include "../engine-core/2D/window2D.h"
#include "../engine-core/2D/renderer2D.h"
#include "objectInstancer.h"

// --- Variables ---
static int last_x = 0, last_y = 0; //Keep track of the last added position, to avoid duplicate entries
static instance_t* blockInstance, *solidBlockInstance;

// --- Functions ---
void objectManagerInit();
void objectManagerRenderObjects();
void objectManagerDeleteAllObjects();
void objectManagerCheckForPlacement();
void objectManagerCleanUp();

#endif