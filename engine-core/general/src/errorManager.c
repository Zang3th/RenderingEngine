#include "errorManager.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while ((error = glGetError()))
    {
        printf("\n");
        log_error("OpenGL Error | Errorcode: %d in %s at line %d\n", error, function, line);
        return false;
    }
    return true;
}