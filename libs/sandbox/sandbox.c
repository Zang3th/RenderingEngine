#include "sandbox.h"

void sandboxInit()
{
    windowInit();
    uiInit();      
}

bool sandboxIsRunning()
{        
    return windowIsRunning();
}

void sandboxPerFrame()
{
    // --- Prepare frame
    windowFrametime();
    windowPrepare();    

    // --- Render
    uiRender();

    // --- End frame
    windowSwapBuffer();
    windowPollEvents();   
}

void sandboxCleanUp()
{
    uiCleanUp(); 
    windowCleanUp();       
}    