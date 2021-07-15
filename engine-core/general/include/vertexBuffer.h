#ifndef VERTEXBUFFER
#define VERTEXBUFFER

#include "../../vendor/include/glad.h"
#include "errorManager.h"

// --- Functions ---
unsigned int createVertexBuffer(const void* data, unsigned int size);
unsigned int createDynamicVertexBuffer(const void* data, unsigned int size);
void deleteVertexBuffer(unsigned int vboID);
void bindVertexBuffer(unsigned int vboID);
void unbindVertexBuffer();
void updateDynamicVertexBuffer(const void* data, unsigned int size);

#endif