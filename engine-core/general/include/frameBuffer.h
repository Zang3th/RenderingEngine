#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include "../../vendor/include/glad.h"
#include "errorManager.h"

// --- Functions ---
unsigned int createFrameBuffer();
void deleteFrameBuffer(unsigned int fboID);
void bindFrameBuffer(unsigned int fboID, unsigned int width, unsigned int height);
void unbindFrameBuffer();
unsigned int createTextureAttachment(unsigned int width, unsigned int height);
unsigned int createDepthBufferAttachment(unsigned int width, unsigned int height);
unsigned int createDepthTextureAttachment(unsigned int width, unsigned int height);
void deleteRenderBuffer(unsigned int rboID);

#endif