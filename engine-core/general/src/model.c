#include "model.h"

void assignStaticMesh(model_t *model, mesh_t* mesh)
{
    //Static model
    model->gotDynamicVBOs = false;
    model->vbos = NULL;

    //Create and bind vao
    unsigned int vao = createVertexArray();
    bindVertexArray(vao);

    //Create and initialize vbo's
    unsigned int vboVertex = createVertexBuffer(mesh->vertices, mesh->verticeCount * sizeof(float));
    defineVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vboTexCoord = createVertexBuffer(mesh->texCoords, mesh->texCoordsCount * sizeof(float));
    defineVertexAttributes(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    unsigned int vboColor = createVertexBuffer(mesh->colors, mesh->colorCount * sizeof(float));
    defineVertexAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vboNormal = createVertexBuffer(mesh->normals, mesh->normalCount * sizeof(float));
    defineVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vboTexSampler = createVertexBuffer(mesh->textureIndex, mesh->texIndexCount * sizeof(float));
    defineVertexAttributes(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

    //Create and initialize ibo
    unsigned int ibo = createIndexBuffer(mesh->indices, mesh->indiceCount * sizeof(unsigned int));

    //Unbind vao, vbo's and delete vbo's
    unbindVertexArray(vao);
    unbindVertexBuffer(vboVertex);
    deleteVertexBuffer(vboVertex);
    unbindVertexBuffer(vboTexCoord);
    deleteVertexBuffer(vboTexCoord);
    unbindVertexBuffer(vboColor);
    deleteVertexBuffer(vboColor);
    unbindVertexBuffer(vboNormal);
    deleteVertexBuffer(vboNormal);
    unbindVertexBuffer(vboTexSampler);
    deleteVertexBuffer(vboTexSampler);
    unbindIndexBuffer();

    //Assign vao and ibo
    model->vao = vao;
    model->ibo = ibo;
}

void assignDynamicMesh(model_t *model, mesh_t* mesh)
{
    //Dynamic model
    model->gotDynamicVBOs = true;
    model->vbos = (vbos_t*)malloc(sizeof(vbos_t));

    //Create and bind vao
    unsigned int vao = createVertexArray();
    bindVertexArray(vao);

    //Create, initialize and save dynamic vbo's
    model->vbos->vboVertex = createDynamicVertexBuffer(mesh->vertices, mesh->verticeCount * sizeof(float));
    defineVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int vboTexCoord = createVertexBuffer(mesh->texCoords, mesh->texCoordsCount * sizeof(float));
    defineVertexAttributes(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    model->vbos->vboColor = createDynamicVertexBuffer(mesh->colors, mesh->colorCount * sizeof(float));
    defineVertexAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    model->vbos->vboNormal = createDynamicVertexBuffer(mesh->normals, mesh->normalCount * sizeof(float));
    defineVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    model->vbos->vboTexSampler = createDynamicVertexBuffer(mesh->textureIndex, mesh->texIndexCount * sizeof(float));
    defineVertexAttributes(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

    //Create and initialize ibo
    unsigned int ibo = createIndexBuffer(mesh->indices, mesh->indiceCount * sizeof(unsigned int));

    //Unbind vao, vbo's and delete vbo's
    unbindVertexArray(vao);
    unbindVertexBuffer(model->vbos->vboVertex);
    unbindVertexBuffer(vboTexCoord);
    deleteVertexBuffer(vboTexCoord);
    unbindVertexBuffer(model->vbos->vboColor);
    unbindVertexBuffer(model->vbos->vboNormal);
    unbindVertexBuffer(model->vbos->vboTexSampler);
    unbindIndexBuffer();

    //Assign vao and ibo
    model->vao = vao;
    model->ibo = ibo;
}

void updateDynamicMesh(model_t *model, mesh_t* mesh)
{
    bindVertexArray(model->vao);

    //Update vertex buffers with the new mesh data
    bindVertexBuffer(model->vbos->vboVertex);
    updateDynamicVertexBuffer(mesh->vertices, mesh->verticeCount * sizeof(float));
    unbindVertexBuffer(model->vbos->vboVertex);

    bindVertexBuffer(model->vbos->vboColor);
    updateDynamicVertexBuffer(mesh->colors, mesh->colorCount * sizeof(float));
    unbindVertexBuffer(model->vbos->vboColor);

    bindVertexBuffer(model->vbos->vboNormal);
    updateDynamicVertexBuffer(mesh->normals, mesh->normalCount * sizeof(float));
    unbindVertexBuffer(model->vbos->vboNormal);

    bindVertexBuffer(model->vbos->vboTexSampler);
    updateDynamicVertexBuffer(mesh->textureIndex, mesh->texIndexCount * sizeof(float));
    unbindVertexBuffer(model->vbos->vboTexSampler);

    unbindVertexArray(model->vao);
}

model_t* createModel(mesh_t* mesh, unsigned int shader, unsigned int* textures, unsigned int texCount, bool dynamicVBOs)
{
    if(texCount < MAX_MODEL_TEXTURES)
    {
        //Create model
        model_t* model = malloc(sizeof(model_t));

        //Assign variables
        model->verticesToRender = mesh->indiceCount;
        model->shader = shader;
        model->textureCount = texCount;

        //Create vao, vbos and ibo out of the mesh data
        if(dynamicVBOs == false)
            assignStaticMesh(model, mesh);
        else
            assignDynamicMesh(model, mesh);

        deleteMesh(mesh);

        //Copy textures
        int texSlotSamplers[texCount];

        for(int i = 0; i < texCount; i++)
        {
            texSlotSamplers[i] = i;  
            model->textures[i] = textures[i];    
        }
        
        //Create uniform texture array for indexing textures
        bindShader(model->shader); 
        setUniform1iv(model->shader, "textureArray", texSlotSamplers, texCount);
        unbindShader();

        //Create model matrix
        mat4 modelMatrix;
        glm_mat4_identity(modelMatrix);
        memcpy(&(model->modelMatrix[0][0]), &(modelMatrix[0][0]), sizeof(float) * 16);
       
        return model;
    }

    log_error("Too many textures for this model!");
    return NULL;
}

void deleteModel(model_t* model)
{
    if(model->gotDynamicVBOs && model->vbos != NULL)
        free(model->vbos);
    deleteIndexBuffer(model->ibo);
    deleteVertexArray(model->vao);
    free(model);
}