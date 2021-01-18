#include "mesh.h"

mesh_t* meshCreate(unsigned int vertices, unsigned int texCoords)
{
    mesh_t* mesh = malloc(sizeof(mesh_t));
    mesh->vertices = malloc(sizeof(float) * vertices);
    mesh->verticeCount = vertices;
    mesh->texCoords = malloc(sizeof(float) * texCoords);
    mesh->texCoordsCount = texCoords;

    return mesh;
}

void meshDestroy(mesh_t* mesh)
{
    free(mesh->vertices);
    free(mesh->texCoords);
    free(mesh);
}