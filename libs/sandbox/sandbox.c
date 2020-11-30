#include "sandbox.h"
#include "../engine-core/texture.h"
#include "../engine-core/shader.h"

void sandboxInit()
{
    windowInit();

    unsigned int* cubeTexture = createTexture("res/textures/Block.jpg");
    bindTexture(cubeTexture);
    
    printVector(3.0f, 5.0f, 1.0f, 1.0f);
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