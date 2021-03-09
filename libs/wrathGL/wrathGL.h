#ifndef WRATHGL
#define WRATHGL

#include "../engine-core/3D/window3D.h"
#include "../engine-core/general/resourceManager.h"
#include "../engine-core/general/renderer.h"
#include "../engine-core/general/textRenderer.h"
#include "../engine-core/general/monitoring.h"
#include "../engine-core/general/mesh.h"
#include "../engine-core/general/meshCreator.h"
#include "../engine-core/general/model.h"
#include "waterRenderer.h"

// --- Variables
static model_t* terrainModel = NULL, *waterModel = NULL;
static sprite_t* keyboardSprite = NULL, *terrainSprite = NULL;

// --- Functions ---
void wrathGLInit();
bool wrathGLIsRunning();
void wrathGLPerFrame();
void wrathGLCleanUp();

#endif