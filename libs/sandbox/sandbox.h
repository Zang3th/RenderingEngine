#ifndef SANDBOX
#define SANDBOX

#include "../engine-core/window.h"
#include "../engine-core/renderer.h"
#include "../engine-core/resourceManager.h"
#include "ui.h"
#include "objectManager.h"
#include "../engine-core/textRenderer.h"

// --- Variables ---
static char* dtAccAvgBuffer;
static char* fpsAvgBuffer;

// --- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandBoxRenderText();
void sandBoxUpdateMonitoring();
void sandboxCleanUp();

#endif