#include "sandbox.h"

void sandboxInit()
{
    //Init modules
    windowInit();
    textRendererInit(); 
    rendererInit();   

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

    //Init modules that depend on resources
    uiInit();  
    objectManagerInit(); 
}

bool sandboxIsRunning()
{        
    return windowIsRunning();
}

void sandboxPerFrame()
{
    // --- Pre render
        // -- Poll events
        windowPollEvents();

        // -- Prepare frame
        windowCalcFrametime();
        windowPrepare();    

    // --- Do render
        // -- Reset drawCall counter for current frame
        drawCalls = 0; 
        uiRenderElements();    

        objectManagerCheckForPlacement();
        objectManagerRenderObjects();    

        // -- Render highlighter last to be on top of everything else
        uiRenderHighlighter(); 

    // --- After render
        windowRenderTitle(drawCalls);

        // -- End frame
        windowSwapBuffer();       
}

void sandboxCleanUp()
{
    objectManagerCleanUp();
    uiCleanUp();
    resourceManagerCleanUp();     
    windowCleanUp();       
}    