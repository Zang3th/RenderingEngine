#ifndef SANDBOX
#define SANDBOX

#include "../engine-core/window.h"
#include "ui.h"
#include "../engine-core/resourceManager.h"
#include "../engine-core/renderer.h"
#include "objectManager.h"

// --- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandboxCleanUp();

#endif