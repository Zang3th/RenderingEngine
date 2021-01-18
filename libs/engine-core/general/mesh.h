#ifndef MESH
#define MESH

#include <stdlib.h>

typedef struct{
    float* vertices;
    float* texCoords;
    unsigned int verticeCount;
    unsigned int texCoordsCount;
} mesh_t;

mesh_t* meshCreate(unsigned int vertices, unsigned int texCoords);
void meshDestroy(mesh_t* mesh);

#endif