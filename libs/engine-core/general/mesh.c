#include "mesh.h"

mesh_t* createMesh(unsigned int vertices, unsigned int texCoords, unsigned int indices)
{
    mesh_t* mesh = malloc(sizeof(mesh_t));
    mesh->vertices = malloc(sizeof(float) * 3 * vertices); //vec3
    mesh->verticeCount = vertices * 3;
    mesh->texCoords = malloc(sizeof(float) * 2 * texCoords); //vec2
    mesh->texCoordsCount = texCoords * 2;
    mesh->indices = malloc(sizeof(unsigned int) * indices); //unsigned int
    mesh->indiceCount = indices;

    return mesh;
}

void debugMesh(mesh_t* mesh)
{
    printf("\n");
    log_info("verticeCount: %d (vertices: %d)", mesh->verticeCount, mesh->verticeCount / 3);
    log_info("texCoordsCount: %d (texCoords: %d)", mesh->texCoordsCount, mesh->texCoordsCount / 2);
    log_info("indiceCount: %d", mesh->indiceCount);

    for(int i = 0; i < mesh->verticeCount - 2; i+=3)
    {
        log_info("x: %f, y: %f, z: %f", 
        mesh->vertices[i], 
        mesh->vertices[i + 1], 
        mesh->vertices[i + 2]);
    }

    for(int i = 0; i < mesh->texCoordsCount - 1; i+=2)
    {
        log_info("tex1: %f, tex2: %f", 
        mesh->texCoords[i], 
        mesh->texCoords[i + 1]);
    }

    for(int i = 0; i < mesh->indiceCount - 2; i+=3)
    {
        log_info("x: %d, y: %d, z: %d", 
        mesh->indices[i], 
        mesh->indices[i + 1], 
        mesh->indices[i + 2]);
    }
    printf("\n");
}

void deleteMesh(mesh_t* mesh)
{
    free(mesh->vertices);
    free(mesh->texCoords);
    free(mesh->indices);
    free(mesh);
}