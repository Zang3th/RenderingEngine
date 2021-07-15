#ifndef POWDERTRAIN
#define POWDERTRAIN

#include "../../../engine-core/2D/include/window2D.h"
#include "../../../engine-core/general/include/renderer.h"
#include "ui_powderTrain.h"
#include "../../../engine-core/general/include/textRenderer.h"
#include "../../../engine-core/general/include/monitoring.h"
#include "particleSystem.h"

// --- Functions ---
void powderTrainInit();
bool powderTrainIsRunning();
void powderTrainPerFrame();
void powderTrainCleanUp();

#endif