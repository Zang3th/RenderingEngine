#include "model.h"
#include "utility.h"

unsigned int createTerrainMeshVAO(mesh_t* mesh)
{
    //Create and bind vao
    unsigned int vao = createVertexArray();
    bindVertexArray(vao);

    //Create and initialize vbo's
    unsigned int vbo_vertex = createVertexBuffer(mesh->vertices, mesh->verticeCount * sizeof(float));
    defineVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vbo_texCoord = createVertexBuffer(mesh->texCoords, mesh->texCoordsCount * sizeof(float));
    defineVertexAttributes(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    unsigned int vbo_color = createVertexBuffer(mesh->colors, mesh->colorCount * sizeof(float));
    defineVertexAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vbo_normal = createVertexBuffer(mesh->normals, mesh->normalCount * sizeof(float));
    defineVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vbo_texSampler = createVertexBuffer(mesh->textureIndex, mesh->texIndexCount * sizeof(float));
    defineVertexAttributes(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

    //Create ib
    unsigned int ibo = createIndexBuffer(mesh->indices, mesh->indiceCount * sizeof(unsigned int));

    //Unbind vao, vbo's and delete vbo's
    unbindVertexArray(vao);
    unbindVertexBuffer(vbo_vertex);
    deleteVertexBuffer(vbo_vertex);
    unbindVertexBuffer(vbo_texCoord);
    deleteVertexBuffer(vbo_texCoord);
    unbindVertexBuffer(vbo_color);
    deleteVertexBuffer(vbo_color);
    unbindVertexBuffer(vbo_normal);
    deleteVertexBuffer(vbo_normal);
    unbindVertexBuffer(vbo_texSampler);
    deleteVertexBuffer(vbo_texSampler);

    return vao;
}

unsigned int createMeshVAO(mesh_t* mesh)
{
    //Create and bind vao
    unsigned int vao = createVertexArray();
    bindVertexArray(vao);

    //Create and initialize vbo's
    unsigned int vbo_vertex = createVertexBuffer(mesh->vertices, mesh->verticeCount * sizeof(float));
    defineVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vbo_texCoord = createVertexBuffer(mesh->texCoords, mesh->texCoordsCount * sizeof(float));
    defineVertexAttributes(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    unsigned int vbo_color = createVertexBuffer(mesh->colors, mesh->colorCount * sizeof(float));
    defineVertexAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vbo_normal = createVertexBuffer(mesh->normals, mesh->normalCount * sizeof(float));
    defineVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Create ib
    unsigned int ibo = createIndexBuffer(mesh->indices, mesh->indiceCount * sizeof(unsigned int));

    //Unbind vao, vbo's and delete vbo's
    unbindVertexArray(vao);
    unbindVertexBuffer(vbo_vertex);
    deleteVertexBuffer(vbo_vertex);
    unbindVertexBuffer(vbo_texCoord);
    deleteVertexBuffer(vbo_texCoord);
    unbindVertexBuffer(vbo_color);
    deleteVertexBuffer(vbo_color);
    unbindVertexBuffer(vbo_normal);
    deleteVertexBuffer(vbo_normal);
    deleteIndexBuffer(ibo);

    return vao;
}

model_t* createTerrainModel(mesh_t* mesh, unsigned int shader, unsigned int dirtTex, unsigned int stoneTex, unsigned int snowTex)
{
    //Create model
    model_t* model = malloc(sizeof(model_t));
    model->vao = createTerrainMeshVAO(mesh);
    model->shader = shader;
    model->textures[0] = dirtTex;
    model->textures[1] = stoneTex;
    model->textures[2] = snowTex;
    model->textureCount = 3;
    model->verticesToRender = mesh->indiceCount;

    //Create uniform texture array for indexing textures
    bindShader(model->shader); 
    int texSlotSamplers[4] = {0, 1, 2};
    setUniform1iv(model->shader, "textureArray", texSlotSamplers, 3);

    //Create model matrix
    mat4 modelMatrix;
    glm_mat4_identity(modelMatrix);
    memcpy(&(model->modelMatrix[0][0]), &(modelMatrix[0][0]), sizeof(float) * 16);

    deleteMesh(mesh);

    return model;
}

model_t* createModel(mesh_t* mesh, unsigned int shader, unsigned int texture)
{
    //Create model
    model_t* model = malloc(sizeof(model_t));
    model->vao = createMeshVAO(mesh);
    model->textures[0] = texture;
    model->textureCount = 1;
    model->shader = shader;
    model->verticesToRender = mesh->indiceCount;

    //Create model matrix
    mat4 modelMatrix;
    glm_mat4_identity(modelMatrix);
    memcpy(&(model->modelMatrix[0][0]), &(modelMatrix[0][0]), sizeof(float) * 16);

    deleteMesh(mesh);

    return model;
}

void deleteModel(model_t* model)
{
    deleteVertexArray(model->vao);
    free(model);
}