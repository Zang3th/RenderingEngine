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
    uiInit_powderTrain();
    pixelRendererInit(WIDTH - 100, HEIGHT);

    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 different characters!
        textRenderingSystemsInit(resourceManagerGetShader("batchTextShader"), resourceManagerGetShader("simpleTextShader"));
        monitoringInit();  

        //Add static text
        uiAddText_powderTrain();    
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
        drawcalls = 0;                   //Reset drawcalls for current frame
        windowPollEvents();
        windowCalcFrametime();
        windowPrepare();    
        pixelRendererSet(100, 100, (vec3){1.0f, 1.0f, 1.0f});
        pixelRendererSet(200, 200, (vec3){0.0f, 1.0f, 0.0f});

    // --- Render
        uiRender_powderTrain();          //Render UI    
        pixelRendererFlush();
        textBatchRendererDisplay();      //Render batched text
        monitoringRenderText(deltaTime); //Render simple text   

    // --- After render
        windowUpdateTitle(drawcalls);
        windowSwapBuffer();              //End frame
}

void powderTrainCleanUp()
{
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    pixelRendererCleanUp();
    uiCleanUp_powderTrain();
    resourceManagerCleanUp();
    windowCleanUp();
}