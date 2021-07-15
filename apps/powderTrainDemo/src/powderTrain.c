#include "powderTrain.h"

void powderTrainLoadResources()
{
    //Load textures
    resourceManagerLoadTexture("sidebarTexture", "../res/textures/powderTrain/Sidebar.jpg");
    resourceManagerLoadTexture("blockTexture", "../res/textures/powderTrain/Block.png");
    resourceManagerLoadTexture("trashcanTexture", "../res/textures/sandbox/Trashcan.png");
    resourceManagerLoadTexture("highlightTexture", "../res/textures/powderTrain/Highlighter.png"); 

    //Load shaders
    resourceManagerLoadShader("standardShader", "../res/shader/sandbox/standard_vs.glsl", "../res/shader/sandbox/standard_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "../res/shader/sandbox/batchText_vs.glsl", "../res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "../res/shader/sandbox/simpleText_vs.glsl", "../res/shader/sandbox/simpleText_fs.glsl");

    //Load sprite data
    resourceManagerLoadSpriteData();
}

void powderTrainInit()
{
    //Init modules
    window2DInit("RenderingEngine - PowderTrain"); 
    rendererInit(NULL); //Init with NULL to use no camera   

    //Load resources
    powderTrainLoadResources();

    //Init modules that depend on resources
    uiInit_powderTrain();
    particleSystemInit();      

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
    return window2DIsRunning();
}

void powderTrainPerFrame()
{
    // --- Pre render
        drawcalls = 0;                   //Reset drawcalls for current frame
        window2DPollEvents();
        window2DCalcFrametime();
        window2DPrepare();    
        particleSystemCheckSpawn();      //Check if new particles need to be spawned  
        
    // --- Render
        particleSystemUpdate();          //Render particles   
        uiRender_powderTrain();          //Render UI            
        textBatchRendererDisplay();      //Render batched text
        monitoringRenderText(deltaTime); //Render simple text   

    // --- After render
        window2DUpdateTitle(drawcalls);
        window2DSwapBuffer();              //End frame
}

void powderTrainCleanUp()
{
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    particleSystemCleanUp();
    uiCleanUp_powderTrain();
    resourceManagerCleanUp();
    window2DCleanUp();
}