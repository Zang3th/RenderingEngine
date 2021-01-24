#ifndef MODEl
#define MODEl

#include "texture.h"
#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "mesh.h"
#include <memory.h>

// --- Variables ---
typedef struct{
    unsigned int* vao;
    unsigned int* texture;
    unsigned int* shader;
    vec3 color;
    mat4 model;
    unsigned int verticesToRender;
} model_t;

// --- Functions ---
unsigned int* createMeshVAO(mesh_t* mesh);
model_t* createModel(mesh_t* mesh, unsigned int* texture, unsigned int* shader, float* color);
void deleteModel(model_t* model);

#endif