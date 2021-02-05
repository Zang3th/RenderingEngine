#include "frameBuffer.h"

const extern unsigned int WIDTH;
const extern unsigned int HEIGHT;

unsigned int createFrameBuffer()
{
    unsigned int fboID;
    GLCall(glGenFramebuffers(1, &fboID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fboID));
    GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));
    return fboID;
}

void deleteFrameBuffer(unsigned int fboID)
{
    GLCall(glDeleteFramebuffers(1, &fboID));
}

void bindFrameBuffer(unsigned int fboID, unsigned int width, unsigned int height)
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0)); //Make sure texture isn't bound
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fboID));
    GLCall(glViewport(0, 0, width, height));
}

void unbindFrameBuffer()
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GLCall(glViewport(0, 0, WIDTH, HEIGHT));
}

unsigned int createTextureAttachment(unsigned int width, unsigned int height)
{
    unsigned int textureID;
    GLCall(glGenTextures(1, &textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0));
    return textureID;
}

unsigned int createDepthBufferAttachment(unsigned int width, unsigned int height)
{
    unsigned int renderBufferID;
    GLCall(glGenRenderbuffers(1, &renderBufferID));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height));
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferID));
    return renderBufferID;
}

unsigned int createDepthTextureAttachment(unsigned int width, unsigned int height)
{
    unsigned int textureID;
    GLCall(glGenTextures(1, &textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureID, 0));
    return textureID;
}

void deleteRenderBuffer(unsigned int rboID)
{
    GLCall(glDeleteRenderbuffers(1, &rboID));
}