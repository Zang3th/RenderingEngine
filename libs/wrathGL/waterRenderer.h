#ifndef WATERRENDERER
#define WATERRENDERER

#include "../engine-core/general/frameBuffer.h"
#include "../engine-core/general/texture.h"

// --- Variables ---
static unsigned int REFLECTION_WIDTH = 640;
static unsigned int REFLECTION_HEIGHT = 320;
static unsigned int REFRACTION_WIDTH = 1280;
static unsigned int REFRACTION_HEIGHT = 720;

extern unsigned int reflectionFBO, reflectionTexture, reflectionDepthBuffer;
extern unsigned int refractionFBO, refractionTexture, refractionDepthTexture;

// --- Functions ---
void initWaterRenderer();
void bindWaterReflectFramebuffer();
void bindWaterRefractFramebuffer();
void cleanUpWaterRenderer();

#endif