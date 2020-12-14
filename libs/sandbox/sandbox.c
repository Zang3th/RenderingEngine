#include "sandbox.h"

void sandboxInit()
{
    windowInit();

    //Load resources
    resourceManagerLoadTexture("blockTexture", "res/textures/Block.jpg");
    resourceManagerLoadTexture("solidBlockTexture", "res/textures/Block_solid.jpg");
    resourceManagerLoadTexture("trashcanTexture", "res/textures/Trashcan.png");
    resourceManagerLoadTexture("backgroundTexture", "res/textures/Background.jpg");
    resourceManagerLoadTexture("sidebarTexture", "res/textures/Sidebar.png");        
    resourceManagerLoadTexture("highlightTexture", "res/textures/Highlighter.png");        
    resourceManagerLoadShader("standardShader", "res/shader/standard_vs.glsl", "res/shader/standard_fs.glsl");
    resourceManagerLoadSpriteData();

    uiInit();         
    rendererInit(); 
    objectManagerInit();
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
    windowFrametime();
    windowPrepare();    

    // --- Render
    uiRenderElements();    

    objectManagerCheckForPlacement();
    objectManagerRenderObjects();
    
    uiRenderHighlighter(); //Render last to be on top of everything else

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