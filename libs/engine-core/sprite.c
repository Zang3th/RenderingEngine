#include "sprite.h"

unsigned int* createVertexData()
{
    //Create and bind vao
    unsigned int* vao = createVertexArray();
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

    //Create vbo, send it data and configure vao
    unsigned int* vbo = createVertexBuffer(vertices, sizeof(vertices));
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    //Unbind vao, vbo and delete vbo
    unbindVertexArray(vao);
    unbindVertexBuffer(vbo);
    deleteVertexBuffer(vbo);

    return vao;
}

Sprite* createSprite(unsigned int* vertexData, unsigned int* texture, unsigned int* shader, float* position, float* size, float rotation, float* baseColor, bool clickable)
{   
    //Create sprite based on given parameters
    Sprite sprite;
    sprite.vertexData = vertexData;
    sprite.texture = texture;
    sprite.shader = shader;
    sprite.basePosition[0] = position[0];
    sprite.basePosition[1] = position[1];
    sprite.baseSize[0] = size[0];
    sprite.baseSize[1] = size[1];
    sprite.baseRotation = rotation;
    sprite.baseColor[0] = baseColor[0];
    sprite.baseColor[1] = baseColor[1];
    sprite.baseColor[2] = baseColor[2];
    glm_vec3_copy(sprite.baseColor, sprite.currentColor);
    sprite.isClickable = clickable;
    sprite.gotClicked = false;

    //Create model matrix and apply transformations
    mat4 model;
    glm_mat4_identity(model);

    glm_translate(model, (vec3){sprite.basePosition[0], sprite.basePosition[1], 1.0f}); //First translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    glm_translate(model, (vec3){sprite.baseSize[0] * 0.5f, sprite.baseSize[1] * 0.5f, 0.0f}); //Move origin of rotation to center of quad
    glm_rotate(model, sprite.baseRotation, (vec3){0.0f, 0.0f, 1.0f}); //Then rotate
    glm_translate(model, (vec3){sprite.baseSize[0] * -0.5f, sprite.baseSize[1] * -0.5f, 0.0f}); //Move origin back

    glm_scale(model, (vec3){sprite.baseSize[0], sprite.baseSize[1], 1.0f});

    glm_mat4_copy(model, sprite.model);    

    //Copy sprite onto the heap and return it
    void* mem = malloc(sizeof(Sprite));
    memcpy(mem, &sprite, sizeof(sprite));

    return (Sprite*)mem;
}

void translateSprite(Sprite* sprite, float* position)
{
    //Create model matrix and apply transformations
    mat4 model;
    glm_mat4_identity(model);

    glm_translate(model, (vec3){position[0], position[1], 1.0f}); //First translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    glm_translate(model, (vec3){sprite->baseSize[0] * 0.5f, sprite->baseSize[1] * 0.5f, 0.0f}); //Move origin of rotation to center of quad
    glm_rotate(model, sprite->baseRotation, (vec3){0.0f, 0.0f, 1.0f}); //Then rotate
    glm_translate(model, (vec3){sprite->baseSize[0] * -0.5f, sprite->baseSize[1] * -0.5f, 0.0f}); //Move origin back

    glm_scale(model, (vec3){sprite->baseSize[0], sprite->baseSize[1], 1.0f});

    glm_mat4_copy(model, sprite->model);  
}

void deleteSprite(Sprite* sprite)
{
    free(sprite);
}

void deleteVertexData(unsigned int* vertexData)
{
    deleteVertexBuffer(vertexData);
}