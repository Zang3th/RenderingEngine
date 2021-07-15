#include "vertexBuffer.h"

unsigned int createVertexBuffer(const void* data, unsigned int size)
{
    unsigned int vboID;
    GLCall(glGenBuffers(1, &vboID));
	bindVertexBuffer(vboID);
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    return vboID;
}

unsigned int createDynamicVertexBuffer(const void* data, unsigned int size)
{
    unsigned int vboID;
    GLCall(glGenBuffers(1, &vboID));
	bindVertexBuffer(vboID);
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    return vboID;
}

void deleteVertexBuffer(unsigned int vboID)
{
    GLCall(glDeleteBuffers(1, &vboID));
}

void bindVertexBuffer(unsigned int vboID)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
}

void unbindVertexBuffer()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void updateDynamicVertexBuffer(const void* data, unsigned int size)
{
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}