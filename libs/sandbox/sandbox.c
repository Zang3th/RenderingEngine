#include "sandbox.h"

void sandboxInit()
{
    //Init modules
    windowInit();     
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
    resourceManagerLoadShader("textShader", "res/shader/text_vs.glsl", "res/shader/text_fs.glsl");
    resourceManagerLoadSpriteData();   

    //Init modules that depend on resources
    uiInit();  
    objectManagerInit(); 
    textRendererInit(resourceManagerGetShader("textShader"));

    //Allocate memory for monitoring buffer
    dtAccAvgBuffer = malloc(sizeof(char) * 20);
    fpsAvgBuffer = malloc(sizeof(float) * 20);
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
        drawcalls = 0; 
        uiRenderElements();    

        objectManagerCheckForPlacement();
        objectManagerRenderObjects();    

        uiRenderHighlighter(); 
        sandBoxRenderText();        

    // --- After render
        windowUpdateTitle(drawcalls);

        // -- End frame
        windowSwapBuffer();       
}

void sandBoxRenderText()
{
    sandBoxUpdateMonitoring();

    textRendererDisplay(&dtAccAvgBuffer[0], 15.0f, HEIGHT - 40.0f, 0.7f, (vec3){0.8f, 0.8f, 0.8f});
    textRendererDisplay(&fpsAvgBuffer[0], 15.0f, HEIGHT - 80.0f, 0.7f, (vec3){0.8f, 0.8f, 0.8f});
}

void sandBoxUpdateMonitoring()
{
    char tempBuffer[10];
    
    strcpy(&dtAccAvgBuffer[0], "Frametime: ");
    snprintf(tempBuffer, sizeof(tempBuffer), "%3.3f", dtAccumulated_avg * 1000);
    strcat(dtAccAvgBuffer, tempBuffer);
    strcat(dtAccAvgBuffer, " ms");
    
    strcpy(&fpsAvgBuffer[0], "FPS: ");
    snprintf(tempBuffer, sizeof(tempBuffer), "%2.3f", framerate_avg);
    strcat(fpsAvgBuffer, tempBuffer);    
}

void sandboxCleanUp()
{
    textRendererCleanUp();
    objectManagerCleanUp();
    uiCleanUp();
    resourceManagerCleanUp();     
    windowCleanUp();     

    free(dtAccAvgBuffer);
    free(fpsAvgBuffer);
}    