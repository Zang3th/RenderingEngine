#ifndef SANDBOX
#define SANDBOX

#include "../../../engine-core/2D/include/window2D.h"
#include "../../../engine-core/general/include/renderer.h"
#include "../../../engine-core/general/include/physicsEngine2D.h"
#include "../../../engine-core/general/include/resourceManager.h"
#include "ui_sandbox.h"
#include "objectManager.h"
#include "../../../engine-core/general/include/textRenderer.h"
#include "../../../engine-core/general/include/monitoring.h"

// --- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandboxCleanUp();

#endif