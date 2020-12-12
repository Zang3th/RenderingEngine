#ifndef OBJECTMANAGER
#define OBJECTMANAGER

#include "ui.h"
#include "../engine-core/renderer.h"

// --- Variables ---
#define SANDBOX_ELEMENTS 2
#define ELEMENT_COUNT_MAX 100

// --- Functions ---
void objectManagerInit();
void objectManagerRenderObjects();
void objectManagerCleanUp();

#endif