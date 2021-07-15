#ifndef VERTEXARRAY
#define VERTEXARRAY

#include "../../vendor/include/glad.h"
#include "errorManager.h"

// --- Functions ---
unsigned int createVertexArray();
void deleteVertexArray(unsigned int vaoID);
void bindVertexArray(unsigned int vaoID);
void unbindVertexArray();
void defineVertexAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
void setAttributeDivisor(GLuint index, GLuint divisor);

#endif