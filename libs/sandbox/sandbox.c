#include "sandbox.h"
   
void sandboxInit()
{
    windowInit();
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