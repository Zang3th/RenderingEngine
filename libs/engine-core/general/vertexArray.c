#include "vertexArray.h"

unsigned int createVertexArray()
{
    unsigned int vaoID;
    GLCall(glGenVertexArrays(1, &vaoID));
    return vaoID;
}

void deleteVertexArray(unsigned int vaoID)
{
    GLCall(glDeleteVertexArrays(1, &vaoID));
}

void bindVertexArray(unsigned int vaoID)
{
    GLCall(glBindVertexArray(vaoID));
}

void unbindVertexArray()
{
    GLCall(glBindVertexArray(0));
}

void defineVertexAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
    GLCall(glVertexAttribPointer(index, size, type, normalized, stride, offset));
    GLCall(glEnableVertexAttribArray(index));
}

void setAttributeDivisor(GLuint index, GLuint divisor)
{
    GLCall(glVertexAttribDivisor(index, divisor));
}