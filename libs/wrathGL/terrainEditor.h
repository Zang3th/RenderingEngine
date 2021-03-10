#ifndef TERRAINEDITOR
#define TERRAINEDITOR

#include "../engine-core/general/model.h"
#include "../engine-core/general/noise.h"
#include "../engine-core/general/mesh.h"
#include "../engine-core/general/meshCreator.h"
#include "../engine-core/general/resourceManager.h"

// --- Variables
extern bool currentlyGenerating;

// --- Functions ---
void terrainEditorGenerateNew(model_t* terrainModel, noise_t* noiseStruct);

#endif