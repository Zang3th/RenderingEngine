#ifndef WRATHGL
#define WRATHGL

#include "../../../engine-core/3D/include/window3D.h"
#include "../../../engine-core/general/include/resourceManager.h"
#include "../../../engine-core/general/include/renderer.h"
#include "../../../engine-core/general/include/textRenderer.h"
#include "../../../engine-core/general/include/monitoring.h"
#include "../../../engine-core/general/include/mesh.h"
#include "../../../engine-core/general/include/meshCreator.h"
#include "../../../engine-core/general/include/model.h"
#include "waterRenderer.h"
#include "terrainEditor.h"
#include <pthread.h>

// --- Variables
static model_t* terrainModel = NULL, *waterModel = NULL;
static sprite_t* keyboardSprite = NULL, *terrainSprite = NULL;
static noise_t* noise = NULL;
static pthread_t* calcTerrainThread = NULL;
static threadArgs_t* threadArgs = NULL;

// --- Functions ---
void wrathGLInit();
bool wrathGLIsRunning();
void wrathGLPerFrame();
void wrathGLCleanUp();

#endif