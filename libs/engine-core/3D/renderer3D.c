#include "renderer3D.h"

unsigned int drawcalls = 0;
unsigned int vertices = 0;

void rendererInit()
{
    glm_perspective(glm_rad(45.0f), (float)WIDTH / (float)HEIGHT, 0.1, 10000.0f, projection); 
}

void renderSimpleModel(model_t* model)
{
        bindShader(model->shader);         

        //Get view matrix
        mat4 viewMatrix;
        cameraGetViewMatrix(camera, viewMatrix);

        setUniformMat4f(model->shader, "view", (float*)viewMatrix);    
        setUniformMat4f(model->shader, "model", (float*)model->model);
        setUniformMat4f(model->shader, "projection", (float*)projection);     
        setUniformVec3f(model->shader, "viewPos", (float*)camera->position);

        for(int i = 0; i < model->textureCount; i++)
            bindTextureToSlot(model->textures[i], i);     

        bindVertexArray(model->vao);

        //Render quad
        GLCall(glDrawElements(GL_TRIANGLES, model->verticesToRender, GL_UNSIGNED_INT, NULL));
        drawcalls++;
        vertices += model->verticesToRender;

        unbindVertexArray();
        unbindTexture();
        unbindShader();
}