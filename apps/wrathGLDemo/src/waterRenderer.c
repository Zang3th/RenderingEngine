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

void initWaterRenderer(camera_t* camera)
{
    initReflectionFBO();
    initRefractionFBO();

    rendererCamera = camera;
}

void bindWaterReflectFramebuffer()
{
    bindFrameBuffer(reflectionFBO, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void bindWaterRefractFramebuffer()
{
    bindFrameBuffer(refractionFBO, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void renderToReflectFramebuffer(model_t* terrain, unsigned int terrainShader)
{
    bindWaterReflectFramebuffer();    
    GLCall(glClearColor(0.2, 0.2, 0.2, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    bindShader(terrainShader);    
    setUniformVec4f(terrainShader, "clippingPlane", (vec4){0.0f, 1.0f, 0.0f, -0.1f});
    float distance = 2 * (rendererCamera->position[1] + 0.01f);
    rendererCamera->position[1] -= distance;
    rendererCamera->pitch = -rendererCamera->pitch;
    cameraUpdate(rendererCamera);
    renderModel(terrain);
    rendererCamera->position[1] += distance;
    rendererCamera->pitch = -rendererCamera->pitch;    
    cameraUpdate(rendererCamera);
    unbindFrameBuffer();
}

void renderToRefractFramebuffer(model_t* terrain, unsigned int terrainShader)
{
    bindWaterRefractFramebuffer();    
    GLCall(glClearColor(0.2, 0.2, 0.2, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    bindShader(terrainShader);
    setUniformVec4f(terrainShader, "clippingPlane", (vec4){0.0f, -1.0f, 0.0f, 2.0f});
    renderModel(terrain);    
    unbindFrameBuffer();
}

void renderWater(model_t* water, float dt)
{
    bindShader(water->shader);
    moveFactor += waveSpeed * (dt);
    moveFactor = fmod(moveFactor, 1);
    setUniform1f(water->shader, "moveFactor", moveFactor);
    setUniformVec3f(water->shader, "cameraPosition", (float*)rendererCamera->position);
    unbindShader();
    renderModel(water);    
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