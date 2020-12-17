#include "objectInstancer.h"

#define MAX_INSTANCES 100

unsigned int* blockTexture, *instancedShader; 
unsigned int* vao, *vbo1, *vbo2;
unsigned int currentInstanceCount;
mat4 modelBuffer[1];

void objectInstancerInit()
{
    currentInstanceCount = 0;

    //Create base object instance
    blockTexture = resourceManagerGetTexture("blockTexture");
    instancedShader = resourceManagerGetShader("instancedShader");

    //Create and bind vao
    vao = createVertexArray();
    bindVertexArray(vao);

    //Create data
    float vertices[] =
    {
        //Position  //Texture
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    //Create vbos, send it data, configure vao and set the attrib divisors

    //vbo1 (vertice data)
    vbo1 = createVertexBuffer(vertices, sizeof(vertices));
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, (vec3){500.0f, 500.0f, 1.0f});
    glm_scale(model, (vec3){100.0f, 100.0f, 1.0f});
    memcpy(&modelBuffer[0], &model, sizeof(mat4));

    //vbo2 (model matrix buffer - maximum size for vertex attributes is a vec4 
    //so we need to send 4 consecutive vec4's to simulate a mat4)   
    vbo2 = createDynamicVertexBuffer(&(modelBuffer[0])[0][0], 1 * 16 * sizeof(float));
    defineVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    setAttributeDivisor(1, 1);
    defineVertexAttributes(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    setAttributeDivisor(2, 1);
    defineVertexAttributes(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    setAttributeDivisor(3, 1);
    defineVertexAttributes(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));
    setAttributeDivisor(4, 1);

    unbindVertexArray(vao);
    unbindVertexBuffer(vbo1);
    unbindVertexBuffer(vbo2);
}

void objectInstancerAddInstance(float* position)
{
    mat4 model;
    glm_mat4_identity(model);

    glm_translate(model, (vec3){position[0], position[1], 1.0f});

    memcpy(&modelBuffer[currentInstanceCount], &model, sizeof(mat4));
    currentInstanceCount++;
}

void objectInstancerRender()
{
    bindShader(instancedShader);         

    mat4 projection;
    glm_ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f, projection);

    vec3 v = {1.0f, 1.0f, 1.0f};
    setUniformVec3f(instancedShader, "color", (float*)v);

    setUniformMat4f(instancedShader, "projection", (float*)projection);

    bindTexture(blockTexture);

    bindVertexArray(vao);

    //Render quad
    //GLCall(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, 1));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

    unbindVertexArray(vao);
    unbindTexture(blockTexture);
    unbindShader(instancedShader);
}