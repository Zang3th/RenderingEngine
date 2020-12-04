#ifndef SHADER
#define SHADER

#include "../../vendor/loading/glad.h"
#include <stdlib.h>
#include "errorManager.h"
#include "../../vendor/logging/log.h"
#include <cglm/cglm.h>

//--- Functions ---
static char* parseShader(const char* filepath);
static unsigned int compileShader(unsigned int shaderType, const char* source);
static unsigned int buildShader(unsigned int vsID, unsigned int fsID);
unsigned int* createShader(const char* vsFilepath, const char* fsFilepath);
void deleteShader(unsigned int* shaderID);
void bindShader(const unsigned int* shaderID);
void unbindShader();

void setUniform1i(const unsigned int* shaderID, const char* name, int value);
void setUniform1f(const unsigned int* shaderID, const char* name, float value);
void setUniform4f(const unsigned int* shaderID, const char* name, float v0, float v1, float v2, float v3);
void setUniformMat4f(const unsigned int* shaderID, const char* name, float* matrix);
void setUniformVec3f(const unsigned int* shaderID, const char* name, float* vector);

#endif