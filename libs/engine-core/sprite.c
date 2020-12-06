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

Sprite* createSprite(unsigned int* vertexData, unsigned int* texture, unsigned int* shader, vec2 position, vec2 size, float rotation, vec3 color)
{   
    Sprite sprite; 

    sprite.vertexData = vertexData;
    sprite.texture = texture;
    sprite.shader = shader;
    sprite.position[0] = position[0];
    sprite.position[1] = position[1];
    sprite.size[0] = size[0];
    sprite.size[1] = size[1];
    sprite.rotation = rotation;
    sprite.color[0] = color[0];
    sprite.color[1] = color[1];
    sprite.color[2] = color[2];

    void* mem = malloc(sizeof(Sprite));
    memcpy(mem, &sprite, sizeof(sprite));

    return (Sprite*)mem;
}

void testSprite(Sprite* sprite)
{
    log_info("vertex: %d", *sprite->vertexData);
    log_info("texture: %d", *sprite->texture);
    log_info("shader: %d", *sprite->shader);
    log_info("pos: %f, %f", sprite->position[0], sprite->position[1]);
    log_info("size: %f, %f", sprite->size[0], sprite->size[1]);
    log_info("rotation: %f, %f", sprite->rotation);
    log_info("color: %f, %f, %f", sprite->color[0], sprite->color[1], sprite->color[2]);
}

void renderSprite(Sprite* sprite)
{
    bindShader(sprite->shader);  

    //Projection matrix
    mat4 projection;
    glm_ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f, projection);

    //Model matrix and transformations 
    mat4 model;
    glm_mat4_identity(model);

    glm_translate(model, (vec3){sprite->position[0], sprite->position[1], 1.0f}); //First translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    glm_translate(model, (vec3){sprite->size[0] * 0.5f, sprite->size[1] * 0.5f, 0.0f}); //Move origin of rotation to center of quad
    glm_rotate(model, sprite->rotation, (vec3){0.0f, 0.0f, 1.0f}); //Then rotate
    glm_translate(model, (vec3){sprite->size[0] * -0.5f, sprite->size[1] * -0.5f, 0.0f}); //Move origin back

    glm_scale(model, (vec3){sprite->size[0], sprite->size[1], 1.0f});

    setUniformVec3f(sprite->shader, "color", sprite->color);
    setUniformMat4f(sprite->shader, "model", (float*)model);
    setUniformMat4f(sprite->shader, "projection", (float*)projection);

    bindTexture(sprite->texture);

    bindVertexArray(sprite->vertexData);

    //Render quad
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void deleteSprite(Sprite* sprite)
{
    free(sprite);
}

void deleteVertexData(unsigned int* vertexData)
{
    deleteVertexBuffer(vertexData);
}