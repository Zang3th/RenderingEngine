#ifndef ERRORMANAGER
#define ERRORMANAGER

#include "../../vendor/include/glad.h"
#include <stdio.h>
#include "../../vendor/include/log.h"
#include <signal.h>

// --- Macros ---
#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// --- Variables ---
static GLenum error;

// --- Functions ---
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif