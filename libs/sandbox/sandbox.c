#include "sandbox.h"

void sandboxInit()
{
    windowInit();

    //Load resources
    resourceManagerLoadTexture("blockTexture", "res/textures/Block.jpg");
    resourceManagerLoadTexture("solidBlockTexture", "res/textures/Block_solid.jpg");
    resourceManagerLoadTexture("pickaxeTexture", "res/textures/Pickaxe.png");
    resourceManagerLoadTexture("backgroundTexture", "res/textures/Background.jpg");
    resourceManagerLoadTexture("sidebarTexture", "res/textures/Sidebar.png");        
    resourceManagerLoadShader("standardShader", "res/shader/standard_vs.glsl", "res/shader/standard_fs.glsl");
    resourceManagerLoadSpriteData();

    uiInit();     
    rendererInit(); 
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
    resourceManagerCleanUp();     
    windowCleanUp();       
}    