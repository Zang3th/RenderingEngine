#include "sandbox.h"

void sandboxLoadResources()
{
    //Load textures
    resourceManagerLoadTexture("blockTexture", "res/textures/sandbox/Crate.jpg");
    resourceManagerLoadTexture("solidBlockTexture", "res/textures/sandbox/Block_solid.jpg");
    resourceManagerLoadTexture("trashcanTexture", "res/textures/sandbox/Trashcan.png");
    resourceManagerLoadTexture("backgroundTexture", "res/textures/sandbox/Background.jpg");
    resourceManagerLoadTexture("sidebarTexture", "res/textures/sandbox/Sidebar.png"); 
    resourceManagerLoadTexture("bucketTexture", "res/textures/sandbox/Bucket.png");
    resourceManagerLoadTexture("stickmanTexture", "res/textures/sandbox/Stickman.png");       
    resourceManagerLoadTexture("highlightTexture", "res/textures/sandbox/Highlighter.png"); 

    //Load shaders       
    resourceManagerLoadShader("standardShader", "res/shader/sandbox/standard_vs.glsl", "res/shader/sandbox/standard_fs.glsl");
    resourceManagerLoadShader("instancedShader", "res/shader/sandbox/instanced_vs.glsl", "res/shader/sandbox/instanced_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "res/shader/sandbox/batchText_vs.glsl", "res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "res/shader/sandbox/simpleText_vs.glsl", "res/shader/sandbox/simpleText_fs.glsl");

    //Load sprite data
    resourceManagerLoadSpriteData();  
}

void sandboxInit()
{
    //Init modules
    windowInit("RenderingEngine - Sandbox");     
    rendererInit(NULL); //Init with NULL to use no camera   
    physicsEngineInit();

    //Load resources
    sandboxLoadResources();

    //Init modules that depend on resources
    uiInit();  
    objectManagerInit();   

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

        // -- Update physics
        phyicsEnginePerFrame(deltaTime);

    // --- Do render
        // -- Reset drawCall counter for current frame
        drawcalls = 0; 
        uiRenderElements();    

        objectManagerCheckForPlacement();
        objectManagerRenderObjects();    

        uiRenderHighlighter(); 

        textBatchRendererDisplay(); 
        monitoringRenderText(deltaTime);   

    // --- After render
        windowUpdateTitle(drawcalls);

        // -- End frame
        windowSwapBuffer();       
}

void sandboxCleanUp()
{
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    objectManagerCleanUp();
    uiCleanUp();
    resourceManagerCleanUp();   
    physicsEngineCleanUp();  
    windowCleanUp();     
}    