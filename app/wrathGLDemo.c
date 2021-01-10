#include "wrathGL/wrathGL.h"

int main()
{
    wrathGLInit();

    while(wrathGLIsRunning())
        wrathGLPerFrame();

    wrathGLCleanUp();
    return 0;
}