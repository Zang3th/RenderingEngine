#ifndef MESH
#define MESH

#include <stdlib.h>
#include "../../../vendor/logging/log.h"
#include <memory.h>

typedef struct{
    float* vertices;
    float* texCoords;
    unsigned int* indices;
    float* colors;
    unsigned int verticeCount;
    unsigned int texCoordsCount;
    unsigned int indiceCount;
    unsigned int colorCount;
} mesh_t;

mesh_t* createMesh(unsigned int vertices, unsigned int texCoords, unsigned int indices);
void debugMesh(mesh_t* mesh);
void deleteMesh(mesh_t* mesh);

#endif