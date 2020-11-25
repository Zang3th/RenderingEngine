#ifndef ERROR_MANAGER
#define ERROR_MANAGER

#include <stdio.h>
#include "../../vendor/logging/log.h"
#include <SDL2/SDL_opengl.h>
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