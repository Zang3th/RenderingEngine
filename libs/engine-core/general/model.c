#include "model.h"
#include "utility.h"

unsigned int* createMeshVAO(mesh_t* mesh)
{
    //Create and bind vao
    unsigned int* vao = createVertexArray();
    bindVertexArray(vao);

    //Create and initialize vbo's
    unsigned int* vbo_v = createVertexBuffer(mesh->vertices, mesh->verticeCount * sizeof(float));
    defineVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int* vbo_t = createVertexBuffer(mesh->texCoords, mesh->texCoordsCount * sizeof(float));
    defineVertexAttributes(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    unsigned int* vbo_c = createVertexBuffer(mesh->colors, mesh->colorCount * sizeof(float));
    defineVertexAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Create ib
    unsigned int* ibo = createIndexBuffer(mesh->indices, mesh->indiceCount * sizeof(unsigned int));

    //Unbind vao, vbo's and delete vbo's
    unbindVertexArray(vao);
    unbindVertexBuffer(vbo_v);
    deleteVertexBuffer(vbo_v);
    unbindVertexBuffer(vbo_t);
    deleteVertexBuffer(vbo_t);
    unbindVertexBuffer(vbo_c);
    deleteVertexBuffer(vbo_c);
    deleteIndexBuffer(ibo);

    return vao;
}

model_t* createModel(mesh_t* mesh, unsigned int* texture, unsigned int* shader)
{
    //Create model
    model_t* model = malloc(sizeof(model_t));
    model->vao = createMeshVAO(mesh);
    model->texture = texture;
    model->shader = shader;
    model->verticesToRender = mesh->indiceCount;

    //Create model matrix
    mat4 modelMatrix;
    glm_mat4_identity(modelMatrix);
    memcpy(&(model->model[0][0]), &(modelMatrix[0][0]), sizeof(float) * 16);

    deleteMesh(mesh);

    return model;
}

void deleteModel(model_t* model)
{
    deleteVertexArray(model->vao);
    free(model);
}