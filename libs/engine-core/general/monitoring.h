#ifndef MONITORING
#define MONITORING

#include <cglm/cglm.h>
#include "textRenderer.h"

// --- Variables ---
static float dtAccumulated_avg = 0.0f;
static float framerate_avg = 0.0f;
static int frameCounter = 0;
static float dtAccumulated = 0.0f;
static char* dtAccAvgBuffer = NULL;
static char* fpsAvgBuffer = NULL;

const extern unsigned int HEIGHT;
const extern unsigned int WIDTH;
extern float dtAccumulated_avg;
extern float framerate_avg;

void monitoringInit();
void monitoringAddText();
void monitoringRenderText(float dt);
void monitoringCleanUp();

#endif