#include "sandbox.h"
#include "../engine-core/texture.h"

void sandboxInit()
{
    windowInit();
    unsigned int* cubeTexture = createTexture("res/textures/Block.jpg");
    bindTexture(cubeTexture);
}

bool sandboxIsRunning()
{        
    return windowIsRunning();
}

void sandboxPerFrame()
{
    windowPollEvents();
    windowRender();
}

void sandboxCleanUp()
{
    windowCleanUp();
}    