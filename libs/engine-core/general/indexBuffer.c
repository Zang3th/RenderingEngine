#include "indexBuffer.h"

unsigned int createIndexBuffer(const void* data, unsigned int size)
{
    unsigned int iboID;
    GLCall(glGenBuffers(1, &iboID));
	bindIndexBuffer(iboID);
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    return iboID;
}

void deleteIndexBuffer(unsigned int iboID)
{
    GLCall(glDeleteBuffers(1, &iboID));
}

void bindIndexBuffer(unsigned int iboID)
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
}

void unbindIndexBuffer()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}