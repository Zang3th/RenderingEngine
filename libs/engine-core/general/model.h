#ifndef MODEl
#define MODEl

#include "texture.h"
#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "mesh.h"
#include <memory.h>

#define MAX_MODEL_TEXTURES 16

// --- Variables ---
typedef struct{
    unsigned int vao;
    unsigned int shader;
    unsigned int textures[MAX_MODEL_TEXTURES];
    unsigned int textureCount;
    mat4 modelMatrix;
    unsigned int verticesToRender;
} model_t;

// --- Functions ---
model_t* createTerrainModel(mesh_t* mesh, unsigned int shader, unsigned int dirtTex, unsigned int grassTex, unsigned int stoneTex, unsigned int snowTex);
model_t* createModel(mesh_t* mesh, unsigned int shader, unsigned int texture);
void deleteModel(model_t* model);

#endif