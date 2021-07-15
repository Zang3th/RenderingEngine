#include "sandbox.h"

void sandboxLoadResources()
{
    //Load textures
    resourceManagerLoadTexture("blockTexture", "../res/textures/sandbox/Crate.jpg");
    resourceManagerLoadTexture("solidBlockTexture", "../res/textures/sandbox/Block_solid.jpg");
    resourceManagerLoadTexture("trashcanTexture", "../res/textures/sandbox/Trashcan.png");
    resourceManagerLoadTexture("backgroundTexture", "../res/textures/sandbox/Background.jpg");
    resourceManagerLoadTexture("sidebarTexture", "../res/textures/sandbox/Sidebar.png"); 
    resourceManagerLoadTexture("bucketTexture", "../res/textures/sandbox/Bucket.png");
    resourceManagerLoadTexture("stickmanTexture", "../res/textures/sandbox/Stickman.png");       
    resourceManagerLoadTexture("highlightTexture", "../res/textures/sandbox/Highlighter.png"); 

    //Load shaders       
    resourceManagerLoadShader("standardShader", "../res/shader/sandbox/standard_vs.glsl", "../res/shader/sandbox/standard_fs.glsl");
    resourceManagerLoadShader("instancedShader", "../res/shader/sandbox/instanced_vs.glsl", "../res/shader/sandbox/instanced_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "../res/shader/sandbox/batchText_vs.glsl", "../res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "../res/shader/sandbox/simpleText_vs.glsl", "../res/shader/sandbox/simpleText_fs.glsl");

    //Load sprite data
    resourceManagerLoadSpriteData();  
}

void sandboxInit()
{
    //Init modules
    window2DInit("RenderingEngine - Sandbox");     
    rendererInit(NULL); //Init with NULL to use no camera   
    physicsEngineInit();

    //Load resources
    sandboxLoadResources();

    //Init modules that depend on resources
    uiInit_sandbox();  
    objectManagerInit();   

    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 different characters!
        textRenderingSystemsInit(resourceManagerGetShader("batchTextShader"), resourceManagerGetShader("simpleTextShader"));
        monitoringInit();  

        //Add static text
        uiAddText_sandbox();    
        monitoringAddText();

        //After all text got added -> create one big buffer out of it, to render all batched text in one drawcall
        textBatchRendererUploadToGPU();    
}

bool sandboxIsRunning()
{        
    return window2DIsRunning();
}

void sandboxPerFrame()
{
    // --- Pre render
        window2DPollEvents();
        window2DCalcFrametime();
        window2DPrepare();    
        drawcalls = 0;                   //Reset drawcalls for current fram
        phyicsEnginePerFrame(deltaTime); //Update physics

    // --- Render
        uiRender_sandbox();               //Render UI   
        objectManagerCheckForPlacement(); //Check for different place modes
        objectManagerRenderObjects();     //Render placed objects
        uiRenderHighlighter_sandbox();    //Render highlighter after objects to be on top
        textBatchRendererDisplay();       //Render batched text
        monitoringRenderText(deltaTime);  //Render simple text

    // --- After render
        window2DUpdateTitle(drawcalls);
        window2DSwapBuffer();               //End frame    
}

void sandboxCleanUp()
{
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    objectManagerCleanUp();
    uiCleanUp_sandbox();
    resourceManagerCleanUp();   
    physicsEngineCleanUp();  
    window2DCleanUp();     
}    