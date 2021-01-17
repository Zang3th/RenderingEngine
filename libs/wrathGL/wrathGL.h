#ifndef WRATHGL
#define WRATHGL

#include "../engine-core/3D/window3D.h"
#include "../engine-core/general/resourceManager.h"
#include "../engine-core/general/sprite.h"
#include "../engine-core/3D/renderer3D.h"
#include "../engine-core/general/textRenderer.h"
#include "../engine-core/general/monitoring.h"

// --- Variables
static sprite_t* testSprite = NULL;

// --- Functions ---
void wrathGLInit();
bool wrathGLIsRunning();
void wrathGLAddText();
void wrathGLRenderText();
void wrathGLPerFrame();
void wrathGLCleanUp();

#endif