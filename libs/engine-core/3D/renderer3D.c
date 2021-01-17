#include "renderer3D.h"
#include <cglm/io.h>

#define CGLM_DEFINE_PRINTS

unsigned int drawcalls = 0;

void rendererInit()
{
    glm_perspective(glm_rad(45.0f), (float)WIDTH / (float)HEIGHT, 0.1, 1000.0f, projection); 
}

void renderSimpleSprite(sprite_t* sprite)
{        
        bindShader(sprite->shader);         

        //Get view matrix
        mat4 viewMatrix;
        cameraGetViewMatrix(camera, viewMatrix);

        setUniformMat4f(sprite->shader, "view", (float*)viewMatrix);    
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