#ifndef MODEl
#define MODEl

#include "texture.h"
#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "mesh.h"
#include <memory.h>
#include <stdlib.h>

#define MAX_MODEL_TEXTURES 16

// --- Variables ---
typedef struct{
    unsigned int vboVertex;
    unsigned int vboColor;
    unsigned int vboNormal;
    unsigned int vboTexSampler;
} vbos_t;

typedef struct{
    bool gotDynamicVBOs;
    vbos_t* vbos;
    unsigned int vao;
    unsigned int ibo;
    unsigned int shader;
    unsigned int textures[MAX_MODEL_TEXTURES];
    unsigned int textureCount;
    mat4 modelMatrix;
    unsigned int verticesToRender;
} model_t;

// --- Functions ---
model_t* createModel(mesh_t* mesh, unsigned int shader, unsigned int* textures, unsigned int texCount, bool dynamicVBOs);
void assignStaticMesh(model_t *model, mesh_t* mesh);
void assignDynamicMesh(model_t *model, mesh_t* mesh);
void updateDynamicMesh(model_t *model, mesh_t* mesh);
void deleteModel(model_t* model);

#endif