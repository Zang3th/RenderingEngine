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

void renderSprite(unsigned int* spriteData, unsigned int* texture, unsigned int* shader, vec3 color)
{
    bindShader(shader);  
    setUniformVec3f(shader, "color", (float*)color);
    bindTexture(texture);
    bindVertexArray(spriteData);

    //Render quad
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void deleteSpriteData(unsigned int* spriteData)
{
    deleteVertexBuffer(spriteData);
}