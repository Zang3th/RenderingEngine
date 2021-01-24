#include "renderer3D.h"

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
        bindVertexArray(sprite->vao);

        //Render quad
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        drawcalls++;

        unbindVertexArray();
        unbindTexture();
        unbindShader();
}

void renderSimpleModel(model_t* model)
{
        bindShader(model->shader);         

        //Get view matrix
        mat4 viewMatrix;
        cameraGetViewMatrix(camera, viewMatrix);

        setUniformMat4f(model->shader, "view", (float*)viewMatrix);    
        setUniformVec3f(model->shader, "color", (float*)model->color);
        setUniformMat4f(model->shader, "model", (float*)model->model);
        setUniformMat4f(model->shader, "projection", (float*)projection);        

        bindTexture(model->texture);
        bindVertexArray(model->vao);

        //Render quad
        GLCall(glDrawElements(GL_TRIANGLES, model->verticesToRender, GL_UNSIGNED_INT, NULL));

        drawcalls++;

        unbindVertexArray();
        unbindTexture();
        unbindShader();
}