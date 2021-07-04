#include "powderTrain.h"

void powderTrainLoadResources()
{
    //Load textures
    resourceManagerLoadTexture("backgroundTexture", "res/textures/powderTrain/Background.jpg");
    resourceManagerLoadTexture("sidebarTexture", "res/textures/powderTrain/Sidebar.jpg");
    resourceManagerLoadTexture("blockTexture", "res/textures/powderTrain/Block.png");
    resourceManagerLoadTexture("trashcanTexture", "res/textures/sandbox/Trashcan.png");
    resourceManagerLoadTexture("highlightTexture", "res/textures/powderTrain/Highlighter.png"); 

    //Load shaders
    resourceManagerLoadShader("standardShader", "res/shader/sandbox/standard_vs.glsl", "res/shader/sandbox/standard_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "res/shader/sandbox/batchText_vs.glsl", "res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "res/shader/sandbox/simpleText_vs.glsl", "res/shader/sandbox/simpleText_fs.glsl");

    //Load sprite data
    resourceManagerLoadSpriteData();
}

void powderTrainInit()
{
    //Init modules
    windowInit("RenderingEngine - PowderTrain"); 
    rendererInit(NULL); //Init with NULL to use no camera   

    //Load resources
    powderTrainLoadResources();

    //Init modules that depend on resources
    uiInit();

    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 different characters!
        textRenderingSystemsInit(resourceManagerGetShader("batchTextShader"), resourceManagerGetShader("simpleTextShader"));
        monitoringInit();  

        //Add static text
        uiAddText();    
        monitoringAddText();

        //After all text got added -> create one big buffer out of it, to render all batched text in one drawcall
        textBatchRendererUploadToGPU(); 
}

bool powderTrainIsRunning()
{
    return windowIsRunning();
}

void powderTrainPerFrame()
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

        textBatchRendererDisplay(); 
        monitoringRenderText(deltaTime);   

    // --- After render
        windowUpdateTitle(drawcalls);

        // -- End frame
        windowSwapBuffer();   
}

void powderTrainCleanUp()
{
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    uiCleanUp();
    resourceManagerCleanUp();
    windowCleanUp();
}