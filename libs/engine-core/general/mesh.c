#include "mesh.h"

mesh_t* createMesh(unsigned int vertices, unsigned int texCoords, unsigned int indices)
{
    //Create mesh
    mesh_t* mesh = malloc(sizeof(mesh_t));

    //Save sizes
    mesh->verticeCount = vertices * 3;
    mesh->texCoordsCount = texCoords * 2;
    mesh->indiceCount = indices;    

    //Allocate memory
    mesh->vertices = malloc(mesh->verticeCount * sizeof(float));      //vec3  
    mesh->texCoords = malloc(mesh->texCoordsCount * sizeof(float));   //vec2    
    mesh->indices = malloc(mesh->indiceCount * sizeof(unsigned int)); //unsigned int

    //Set memory
    memset(&(mesh->vertices[0]), 0, mesh->verticeCount * sizeof(float));
    memset(&(mesh->texCoords[0]), 0, mesh->texCoordsCount * sizeof(float));
    memset(&(mesh->indices[0]), 0, mesh->indiceCount * sizeof(unsigned int));

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