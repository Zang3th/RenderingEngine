#ifndef TERRAINEDITOR
#define TERRAINEDITOR

#include "../engine-core/general/model.h"
#include "../engine-core/general/noise.h"
#include "../engine-core/general/mesh.h"
#include "../engine-core/general/meshCreator.h"
#include "../engine-core/general/resourceManager.h"
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