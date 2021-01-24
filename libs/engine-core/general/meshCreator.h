#ifndef MESHCREATOR
#define MESHCREATOR

#include "mesh.h"
#include "../../../vendor/logging/log.h"
#include <memory.h>

mesh_t* meshCreatorPlane(unsigned int size, float tileSize);
mesh_t* meshCreatorOneTile();

#endif