#include "renderer.h"

unsigned int drawcalls = 0;
unsigned int vertices = 0;
const extern unsigned int WIDTH;
const extern unsigned int HEIGHT;
extern unsigned int reflectionTexture;
extern unsigned int refractionTexture;

void rendererInit(camera_t* camera)
{
    glm_perspective(glm_rad(45.0f), (float)WIDTH / (float)HEIGHT, 0.1, 10000.0f, perspectiveProj); 
    glm_ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f, orthoProj);

    rendererCamera = camera;
}

void renderSprite(sprite_t* sprite)
{        
        bindShader(sprite->shader);         

        setUniformVec3f(sprite->shader, "color", (float*)sprite->currentColor);
        setUniformMat4f(sprite->shader, "model", (float*)sprite->model);
        setUniformMat4f(sprite->shader, "projection", (float*)orthoProj);

        bindTexture(sprite->texture);
        bindVertexArray(sprite->vao);

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
        setUniformMat4f(instance->shader, "projection", (float*)orthoProj);

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

void renderModel(model_t* model)
{
        bindShader(model->shader);         

        mat4 viewMatrix;
        cameraGetViewMatrix(rendererCamera, viewMatrix);

        setUniformMat4f(model->shader, "view", (float*)viewMatrix);    
        setUniformMat4f(model->shader, "model", (float*)model->modelMatrix);
        setUniformMat4f(model->shader, "projection", (float*)perspectiveProj);     
        setUniformVec3f(model->shader, "viewPos", (float*)rendererCamera->position);

        for(int i = 0; i < model->textureCount; i++)
            bindTextureToSlot(model->textures[i], i);     

        bindVertexArray(model->vao);

        //Render model
        GLCall(glDrawElements(GL_TRIANGLES, model->verticesToRender, GL_UNSIGNED_INT, NULL));
        drawcalls++;
        vertices += model->verticesToRender;

        unbindVertexArray();
        unbindTexture();
        unbindShader();
}