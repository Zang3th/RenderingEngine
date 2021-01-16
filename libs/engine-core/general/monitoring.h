#ifndef MONITORING
#define MONITORING

#include <cglm/cglm.h>
#include "textRenderer.h"

// --- Variables ---
static float dtAccumulated_avg;
static float framerate_avg;
static int frameCounter;
static float dtAccumulated;
static char* dtAccAvgBuffer;
static char* fpsAvgBuffer;

const extern unsigned int HEIGHT;
const extern unsigned int WIDTH;
extern float dtAccumulated_avg;
extern float framerate_avg;

void monitoringInit();
void monitoringAddText();
void monitoringRenderText(float dt);
void monitoringCleanUp();

#endif