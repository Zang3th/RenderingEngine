#include "mesh.h"

mesh_t* createTerrainMesh(unsigned int vertices, unsigned int texCoords, unsigned int indices)
{
    //Create mesh
    mesh_t* mesh = malloc(sizeof(mesh_t));

    //Save sizes
    mesh->verticeCount = vertices * 3;
    mesh->texCoordsCount = texCoords * 2;
    mesh->indiceCount = indices * 6;  
    mesh->colorCount = mesh->verticeCount;
    mesh->normalCount = mesh->verticeCount;
    mesh->texIndexCount = vertices;

    //Allocate memory
    mesh->vertices = malloc(mesh->verticeCount * sizeof(float));      //vec3  
    mesh->texCoords = malloc(mesh->texCoordsCount * sizeof(float));   //vec2    
    mesh->indices = malloc(mesh->indiceCount * sizeof(unsigned int)); //6 * unsigned int
    mesh->colors = malloc(mesh->colorCount * sizeof(float));          //vec3
    mesh->normals = malloc(mesh->normalCount * sizeof(float));        //vec3
    mesh->textureIndex = malloc(mesh->texIndexCount * sizeof(float)); //float  

    //Set memory
    memset(&(mesh->vertices[0]), 0, mesh->verticeCount * sizeof(float));
    memset(&(mesh->texCoords[0]), 0, mesh->texCoordsCount * sizeof(float));
    memset(&(mesh->indices[0]), 0, mesh->indiceCount * sizeof(unsigned int));
    memset(&(mesh->colors[0]), 0, mesh->colorCount * sizeof(float));
    memset(&(mesh->normals[0]), 0, mesh->normalCount * sizeof(float));
    memset(&(mesh->textureIndex[0]), 0, mesh->texIndexCount * sizeof(float));

    return mesh;
}

mesh_t* createMesh(unsigned int vertices, unsigned int texCoords, unsigned int indices)
{
    //Create mesh
    mesh_t* mesh = malloc(sizeof(mesh_t));

    //Save sizes
    mesh->verticeCount = vertices * 3;
    mesh->texCoordsCount = texCoords * 2;
    mesh->indiceCount = indices * 6;  
    mesh->colorCount = mesh->verticeCount;
    mesh->normalCount = mesh->verticeCount;
    mesh->texIndexCount = 0;

    //Allocate memory
    mesh->vertices = malloc(mesh->verticeCount * sizeof(float));      //vec3  
    mesh->texCoords = malloc(mesh->texCoordsCount * sizeof(float));   //vec2    
    mesh->indices = malloc(mesh->indiceCount * sizeof(unsigned int)); //6 * unsigned int
    mesh->colors = malloc(mesh->colorCount * sizeof(float));          //vec3
    mesh->normals = malloc(mesh->normalCount * sizeof(float));        //vec3
    mesh->textureIndex = NULL;  

    //Set memory
    memset(&(mesh->vertices[0]), 0, mesh->verticeCount * sizeof(float));
    memset(&(mesh->texCoords[0]), 0, mesh->texCoordsCount * sizeof(float));
    memset(&(mesh->indices[0]), 0, mesh->indiceCount * sizeof(unsigned int));
    memset(&(mesh->colors[0]), 0, mesh->colorCount * sizeof(float));
    memset(&(mesh->normals[0]), 0, mesh->normalCount * sizeof(float));

    return mesh;
}

void debugMesh(mesh_t* mesh)
{
    printf("\n");
    
    log_info("verticeCount: %d (vertices: %d)", mesh->verticeCount, mesh->verticeCount / 3);
    log_info("texCoordsCount: %d (texCoords: %d)", mesh->texCoordsCount, mesh->texCoordsCount / 2);
    log_info("indiceCount: %d", mesh->indiceCount);
    log_info("colorCount: %d (colors: %d)", mesh->colorCount, mesh->colorCount / 3);
    log_info("normalCount: %d (normals: %d)", mesh->normalCount, mesh->normalCount / 3);
    log_info("texIndexCount: %d", mesh->texIndexCount);
    
/*     for(int i = 0; i < mesh->verticeCount - 2; i+=3)
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
        log_info("i0: %d, i1: %d, i2: %d", 
        mesh->indices[i], 
        mesh->indices[i + 1], 
        mesh->indices[i + 2]);
    }

    for(int i = 0; i < mesh->colorCount - 2; i+=3)
    {
        log_info("r: %f, g: %f, b: %f", 
        mesh->colors[i], 
        mesh->colors[i + 1], 
        mesh->colors[i + 2]);
    }
     
    for(int i = 0; i < mesh->normalCount - 2; i+=3)
    {
        log_info("x: %f, y: %f, z: %f", 
        mesh->normals[i], 
        mesh->normals[i + 1], 
        mesh->normals[i + 2]);
    }

    for(int i = 0; i < mesh->texIndexCount; i++)
    {
        log_info("index: %f", 
        mesh->textureIndex[i]);
    } */

    printf("\n");
}

void deleteMesh(mesh_t* mesh)
{
    free(mesh->vertices);
    free(mesh->texCoords);
    free(mesh->indices);
    free(mesh->colors);
    free(mesh->normals);
    if(mesh->textureIndex != NULL)
        free(mesh->textureIndex);
    free(mesh);
}