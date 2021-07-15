#ifndef TERRAINEDITOR
#define TERRAINEDITOR

#include "../../../engine-core/general/include/model.h"
#include "../../../engine-core/general/include/noise.h"
#include "../../../engine-core/general/include/random.h"
#include "../../../engine-core/general/include/mesh.h"
#include "../../../engine-core/general/include/meshCreator.h"
#include "../../../engine-core/general/include/resourceManager.h"
#include <pthread.h>

// --- Variables
extern bool currentlyGenerating;
extern bool finishedGenerating;
extern pthread_mutex_t lock;

typedef struct{
    noise_t* noise;
    mesh_t* resultMesh;
} threadArgs_t;

// --- Functions ---
void* terrainEditorStartThread(void* args);
mesh_t* terrainEditorGenerateNew(noise_t* noiseStruct);

#endif