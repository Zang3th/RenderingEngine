#ifndef SANDBOX
#define SANDBOX

#include "../engine-core/2D/window2D.h"
#include "../engine-core/2D/renderer2D.h"
#include "../engine-core/2D/physicsEngine2D.h"
#include "../engine-core/general/resourceManager.h"
#include "ui.h"
#include "objectManager.h"
#include "../engine-core/general/textRenderer.h"
#include "../engine-core/general/monitoring.h"

// --- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandboxCleanUp();

#endif