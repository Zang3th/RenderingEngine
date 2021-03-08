#ifndef WATERRENDERER
#define WATERRENDERER

#include "../engine-core/general/frameBuffer.h"
#include "../engine-core/general/texture.h"
#include "../engine-core/general/model.h"
#include "../engine-core/general/camera.h"
#include "../engine-core/general/renderer.h"

// --- Variables ---
static unsigned int REFLECTION_WIDTH = 640;
static unsigned int REFLECTION_HEIGHT = 320;
static unsigned int REFRACTION_WIDTH = 1280;
static unsigned int REFRACTION_HEIGHT = 720;
static camera_t* waterRendererCamera;
static float moveFactor = 0.0f, waveSpeed = 0.02f;

extern unsigned int reflectionFBO, reflectionTexture, reflectionDepthBuffer;
extern unsigned int refractionFBO, refractionTexture, refractionDepthTexture;

// --- Functions ---
void initWaterRenderer(camera_t* camera);
void bindWaterReflectFramebuffer();
void bindWaterRefractFramebuffer();
void renderToReflectFramebuffer(model_t* terrain, unsigned int terrainShader);
void renderToRefractFramebuffer(model_t* terrain, unsigned int terrainShader);
void renderWater(model_t* water, float dt);
void cleanUpWaterRenderer();

#endif