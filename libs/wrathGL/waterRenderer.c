#include "waterRenderer.h"

unsigned int reflectionFBO = 0, reflectionTexture = 0, reflectionDepthBuffer = 0;
unsigned int refractionFBO = 0, refractionTexture = 0, refractionDepthTexture = 0;

void initReflectionFBO()
{
    reflectionFBO = createFrameBuffer();
    reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    unbindFrameBuffer();
}

void initRefractionFBO()
{
    refractionFBO = createFrameBuffer();
    refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    unbindFrameBuffer();
}

void initWaterRenderer()
{
    initReflectionFBO();
    initRefractionFBO();
}

void bindWaterReflectFramebuffer()
{
    bindFrameBuffer(reflectionFBO, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void bindWaterRefractFramebuffer()
{
    bindFrameBuffer(refractionFBO, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void renderToReflectFramebuffer(camera_t* camera, model_t* terrain, unsigned int terrainShader)
{
    bindWaterReflectFramebuffer();    
    GLCall(glClearColor(0.2, 0.2, 0.2, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    bindShader(terrainShader);    
    setUniformVec4f(terrainShader, "clippingPlane", (vec4){0.0f, 1.0f, 0.0f, -0.01f});
    float distance = 2 * (camera->position[1] + 0.01f);
    camera->position[1] -= distance;
    camera->pitch = -camera->pitch;
    cameraUpdate(camera);
    renderModel(terrain);
    camera->position[1] += distance;
    camera->pitch = -camera->pitch;    
    cameraUpdate(camera);
    unbindFrameBuffer();
}

void renderToRefractFramebuffer(model_t* terrain, unsigned int terrainShader)
{
    bindWaterRefractFramebuffer();    
    GLCall(glClearColor(0.2, 0.2, 0.2, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    bindShader(terrainShader);
    setUniformVec4f(terrainShader, "clippingPlane", (vec4){0.0f, -1.0f, 0.0f, 0.01f});
    renderModel(terrain);    
    unbindFrameBuffer();
}

void cleanUpWaterRenderer()
{
    deleteFrameBuffer(reflectionFBO);
    deleteFrameBuffer(refractionFBO);
    deleteTexture(reflectionTexture);
    deleteTexture(refractionTexture);
    deleteTexture(refractionDepthTexture);
    deleteRenderBuffer(reflectionDepthBuffer);
}