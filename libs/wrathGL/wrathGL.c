#include "wrathGL.h"

void wrathGLInit()
{
    //Init modules
    windowInit();   
}

bool wrathGLIsRunning()
{
    return windowIsRunning();
}

void wrathGLPerFrame()
{
    // --- Pre render
        windowCalcFrametime();
        windowPollEvents();
        windowProcessEvents();
        windowPrepare();         

    // --- Do render

    // --- After render
        windowSwapBuffer(); 
}

void wrathGLCleanUp()
{
    windowCleanUp(); 
}