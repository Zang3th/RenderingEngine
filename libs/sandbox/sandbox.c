#include "sandbox.h"

void sandboxInit()
{
    windowInit();

    //Load resources
    resourceManagerLoadTexture("blockTexture", "res/textures/Crate.jpg");
    resourceManagerLoadTexture("solidBlockTexture", "res/textures/Block_solid.jpg");
    resourceManagerLoadTexture("trashcanTexture", "res/textures/Trashcan.png");
    resourceManagerLoadTexture("backgroundTexture", "res/textures/Background.jpg");
    resourceManagerLoadTexture("sidebarTexture", "res/textures/Sidebar.png"); 
    resourceManagerLoadTexture("bucketTexture", "res/textures/Bucket.png");
    resourceManagerLoadTexture("stickmanTexture", "res/textures/Stickman.png");       
    resourceManagerLoadTexture("highlightTexture", "res/textures/Highlighter.png");        
    resourceManagerLoadShader("standardShader", "res/shader/standard_vs.glsl", "res/shader/standard_fs.glsl");
    resourceManagerLoadShader("instancedShader", "res/shader/instanced_vs.glsl", "res/shader/instanced_fs.glsl");
    resourceManagerLoadSpriteData();

    uiInit();         
    rendererInit(); 
    objectManagerInit();

    objectInstancerInit();
}

bool sandboxIsRunning()
{        
    return windowIsRunning();
}

void sandboxPerFrame()
{
    // --- Poll events
    windowPollEvents();

    // --- Prepare frame
    windowCalcFrametime();
    windowPrepare();    

    // --- Render
    drawCalls = 0; //Reset drawCall counter for current frame
    uiRenderElements();    

    objectManagerCheckForPlacement();
    objectManagerRenderObjects();

    objectInstancerRender();

    uiRenderHighlighter(); //Render last to be on top of everything else

    // --- After render
    windowRenderTitle(drawCalls);

    // --- End frame
    windowSwapBuffer();       
}

void sandboxCleanUp()
{
    objectManagerCleanUp();
    uiCleanUp();
    resourceManagerCleanUp();     
    windowCleanUp();       
}    