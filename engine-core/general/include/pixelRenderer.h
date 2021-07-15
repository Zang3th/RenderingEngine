#ifndef PIXEL_RENDERER
#define PIXEL_RENDERER

#include "errorManager.h"
#include "sprite.h"
#include "renderer.h"
#include "../../vendor/include/log.h"

// --- Macros ---
#define CANVAS_HEIGHT 900
#define CANVAS_WIDTH 1500

// --- Variables ---
static unsigned char backgroundImage[CANVAS_HEIGHT][CANVAS_WIDTH][3];
static unsigned char pixelArray[CANVAS_HEIGHT][CANVAS_WIDTH][3];
static unsigned int textureID;
static sprite_t* image = NULL;

// --- Functions ---
void pixelRendererInit(const char* bgImagePath);
void pixelRendererSet(unsigned int x, unsigned int y, float color[3]);
void pixelRendererReset(unsigned int x, unsigned int y);
void pixelRendererFlush();
void pixelRendererCleanUp();

#endif