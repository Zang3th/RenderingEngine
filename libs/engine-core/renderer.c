#include "renderer.h"

int drawCalls = 0;

void rendererInit()
{
    glm_ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f, projection);
}

void renderSimpleSprite(Sprite* sprite)
{        
        bindShader(sprite->shader);         

        setUniformVec3f(sprite->shader, "color", (float*)sprite->currentColor);
        setUniformMat4f(sprite->shader, "model", (float*)sprite->model);
        setUniformMat4f(sprite->shader, "projection", (float*)projection);

        bindTexture(sprite->texture);

        bindVertexArray(sprite->vertexData);

        //Render quad
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        drawCalls++;

        unbindVertexArray(sprite->vertexData);
        unbindTexture(sprite->texture);
        unbindShader(sprite->shader);
}