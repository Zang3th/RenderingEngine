#ifndef OBJECTMANAGER
#define OBJECTMANAGER

#include "ui.h"
#include "../engine-core/window.h"
#include "../engine-core/renderer.h"
#include "objectInstancer.h"

// --- Variables ---
static int last_x = 0, last_y = 0; //Keep track of the last added position, to avoid duplicate entries
static ObjInstance* blockInstance, *solidBlockInstance;

// --- Functions ---
void objectManagerInit();
void objectManagerRenderObjects();
void objectManagerDeleteAllObjects();
void objectManagerCheckForPlacement();
void objectManagerCleanUp();

#endif