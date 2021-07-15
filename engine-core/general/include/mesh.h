#ifndef MESH
#define MESH

#include <stdlib.h>
#include "../../vendor/include/log.h"
#include <memory.h>

// --- Variables ---
typedef struct{
    float* vertices;
    float* texCoords;
    unsigned int* indices;
    float* colors;
    float* normals;
    float* textureIndex;
    unsigned int verticeCount;
    unsigned int texCoordsCount;
    unsigned int indiceCount;
    unsigned int colorCount;
    unsigned int normalCount;
    unsigned int texIndexCount;
} mesh_t;

// --- Functions ---
mesh_t* createTerrainMesh(unsigned int vertices, unsigned int texCoords, unsigned int indices);
mesh_t* createMesh(unsigned int vertices, unsigned int texCoords, unsigned int indices);
void debugMesh(mesh_t* mesh);
void deleteMesh(mesh_t* mesh);

#endif