#include "renderer.h"

unsigned int drawcalls = 0;

void rendererInit()
{
    glm_ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f, projection);
}

void renderSimpleSprite(sprite_t* sprite)
{        
        bindShader(sprite->shader);         

        setUniformVec3f(sprite->shader, "color", (float*)sprite->currentColor);
        setUniformMat4f(sprite->shader, "model", (float*)sprite->model);
        setUniformMat4f(sprite->shader, "projection", (float*)projection);

        bindTexture(sprite->texture);

        bindVertexArray(sprite->vertexData);

        //Render quad
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        drawcalls++;

        unbindVertexArray();
        unbindTexture();
        unbindShader();
}

void renderInstancedSprite(instance_t* instance)
{
    if(instance->instanceAmount > 0)
    {
        //Set world transform for all instances
        objectInstancerSetWorldtransform(instance);

        bindShader(instance->shader);       

        setUniformVec3f(instance->shader, "color", (float*)instance->color);
        setUniformMat4f(instance->shader, "projection", (float*)projection);

        bindTexture(instance->texture);

        bindVertexArray(instance->vao);

        //Render quad
        GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instance->instanceAmount));
        drawcalls++;

        unbindVertexArray();
        unbindTexture();
        unbindShader();
    }    
}