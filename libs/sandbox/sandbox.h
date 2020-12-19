#ifndef SANDBOX
#define SANDBOX

#include "../engine-core/window.h"
#include "../engine-core/textRenderer.h"
#include "../engine-core/renderer.h"
#include "ui.h"
#include "objectManager.h"
#include "../engine-core/resourceManager.h"

// --- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandboxCleanUp();

#endif