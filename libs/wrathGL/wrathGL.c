#include "wrathGL.h"

void wrathGLInit()
{
    //Create camera
    camera = cameraCreate((vec3){0.0f, 0.0f, 0.0f}, 0.0f, 90.0f);

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
    cameraDestroy(camera);
    windowCleanUp(); 
}