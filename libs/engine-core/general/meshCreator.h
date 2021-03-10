#ifndef MESHCREATOR
#define MESHCREATOR

#include "mesh.h"
#include "../../../vendor/logging/log.h"
#include <memory.h>
#include "noise.h"
#include <cglm/cglm.h>

// --- Functions ---
mesh_t* meshCreatorTerrain(unsigned int size, float tileSize, noise_t* noiseStruct);
mesh_t* meshCreatorPlane(unsigned int size, float tileSize);
mesh_t* meshCreatorOneTile(float size);

#endif