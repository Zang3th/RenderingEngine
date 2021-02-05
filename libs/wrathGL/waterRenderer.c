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

void cleanUpWaterRenderer()
{
    deleteFrameBuffer(reflectionFBO);
    deleteFrameBuffer(refractionFBO);
    deleteTexture(reflectionTexture);
    deleteTexture(refractionTexture);
    deleteTexture(refractionDepthTexture);
    deleteRenderBuffer(reflectionDepthBuffer);
}