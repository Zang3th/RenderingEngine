#ifndef PIXEL_RENDERER
#define PIXEL_RENDERER

#include "errorManager.h"
#include "sprite.h"
#include "renderer.h"

// --- Variables ---

// --- Functions ---
void pixelRendererInit(unsigned int width, unsigned int height);
void pixelRendererSet(unsigned int x, unsigned int y, float color[3]);
void pixelRendererFlush();
void pixelRendererCleanUp();

#endif