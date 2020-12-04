#include "sprite.h"

unsigned int* initSpriteData()
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

void renderSprite(unsigned int* spriteData, unsigned int* texture, unsigned int* shader, vec2 position, vec2 size, float rotation, vec3 color)
{
    bindShader(shader);  

    //Projection matrix
    mat4 projection;
    glm_ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f, projection);

    //Model matrix and transformations 
    mat4 model;
    glm_mat4_identity(model);

    glm_translate(model, (vec3){position[0], position[1], 1.0f}); //First translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    glm_translate(model, (vec3){size[0] * 0.5f, size[1] * 0.5f, 0.0f}); //Move origin of rotation to center of quad
    glm_rotate(model, rotation, (vec3){0.0f, 0.0f, 1.0f}); //Then rotate
    glm_translate(model, (vec3){size[0] * -0.5f, size[1] * -0.5f, 0.0f}); //Move origin back

    glm_scale(model, (vec3){size[0], size[1], 1.0f});

    setUniformVec3f(shader, "color", color);
    setUniformMat4f(shader, "model", (float*)model);
    setUniformMat4f(shader, "projection", (float*)projection);

    bindTexture(texture);

    bindVertexArray(spriteData);

    //Render quad
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void deleteSpriteData(unsigned int* spriteData)
{
    deleteVertexBuffer(spriteData);
}