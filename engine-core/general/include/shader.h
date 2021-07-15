#ifndef SHADER
#define SHADER

#include "../../vendor/include/glad.h"
#include <stdlib.h>
#include "errorManager.h"
#include "../../vendor/include/log.h"
#include <cglm/cglm.h>

// --- Functions ---
char* parseShader(const char* filepath);
unsigned int compileShader(unsigned int shaderType, const char* source);
unsigned int buildShader(unsigned int vsID, unsigned int fsID);
unsigned int createShader(const char* vsFilepath, const char* fsFilepath);
void deleteShader(unsigned int shaderID);
void bindShader(unsigned int shaderID);
void unbindShader();

void setUniform1i(unsigned int shaderID, const char* name, int value);
void setUniform1f(unsigned int shaderID, const char* name, float value);
void setUniform4f(unsigned int shaderID, const char* name, float v0, float v1, float v2, float v3);
void setUniformMat4f(unsigned int shaderID, const char* name, float* matrix);
void setUniformVec3f(unsigned int shaderID, const char* name, float* vector);
void setUniformVec4f(unsigned int shaderID, const char* name, float* vector);
void setUniform1iv(unsigned int shaderID, const char* name, int* values, unsigned int size);

#endif