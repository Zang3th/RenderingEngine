#ifndef SHADER
#define SHADER

#include "../../vendor/loading/glad.h"
#include <stdlib.h>
#include "errorManager.h"
#include "../../vendor/logging/log.h"

//--- Functions ---
static char* parseShader(const char* filepath);
static unsigned int compileShader(unsigned int shaderType, const char* source);
unsigned int* buildShader(unsigned int vsID, unsigned int fsID);
unsigned int* createShader(const char* vsFilepath, const char* fsFilepath);
void deleteShader(unsigned int* shaderID);
void bindShader(const unsigned int* shaderID);
void unbindShader();

#endif