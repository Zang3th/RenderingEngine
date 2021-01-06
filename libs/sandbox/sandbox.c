#include "sandbox.h"

void sandboxInit()
{
    //Init modules
    windowInit();     
    rendererInit();   
    physicsEngineInit();

    //Load resources
    resourceManagerLoadTexture("blockTexture", "res/textures/sandbox/Crate.jpg");
    resourceManagerLoadTexture("solidBlockTexture", "res/textures/sandbox/Block_solid.jpg");
    resourceManagerLoadTexture("trashcanTexture", "res/textures/sandbox/Trashcan.png");
    resourceManagerLoadTexture("backgroundTexture", "res/textures/sandbox/Background.jpg");
    resourceManagerLoadTexture("sidebarTexture", "res/textures/sandbox/Sidebar.png"); 
    resourceManagerLoadTexture("bucketTexture", "res/textures/sandbox/Bucket.png");
    resourceManagerLoadTexture("stickmanTexture", "res/textures/sandbox/Stickman.png");       
    resourceManagerLoadTexture("highlightTexture", "res/textures/sandbox/Highlighter.png");        
    resourceManagerLoadShader("standardShader", "res/shader/sandbox/standard_vs.glsl", "res/shader/sandbox/standard_fs.glsl");
    resourceManagerLoadShader("instancedShader", "res/shader/sandbox/instanced_vs.glsl", "res/shader/sandbox/instanced_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "res/shader/sandbox/batchText_vs.glsl", "res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "res/shader/sandbox/simpleText_vs.glsl", "res/shader/sandbox/simpleText_fs.glsl");
    resourceManagerLoadSpriteData();   

    //Init modules that depend on resources
    uiInit();  
    objectManagerInit();   

    //Allocate memory for monitoring buffer
    dtAccAvgBuffer = malloc(sizeof(float));
    fpsAvgBuffer = malloc(sizeof(float));

    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 different characters!
        textRenderingSystemsInit(resourceManagerGetShader("batchTextShader"), resourceManagerGetShader("simpleTextShader"));

        //Add text
        uiAddText();
        sandboxAddStaticText();        

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
        sandboxRenderText();   

    // --- After render
        windowUpdateTitle(drawcalls);

        // -- End frame
        windowSwapBuffer();       
}

void sandboxRenderText()
{
    sandboxUpdateMonitoring();

    textSimpleRendererDisplay(&dtAccAvgBuffer[0], 170.0f, HEIGHT - 40.0f, 0.7f, (vec3){0.8f, 0.8f, 0.8f});
    textSimpleRendererDisplay(&fpsAvgBuffer[0], 75.0f, HEIGHT - 80.0f, 0.7f, (vec3){0.8f, 0.8f, 0.8f});
}

void sandboxUpdateMonitoring()
{
    snprintf(&dtAccAvgBuffer[0], sizeof(dtAccAvgBuffer), "%2.2f", dtAccumulated_avg * 1000);
    snprintf(&fpsAvgBuffer[0], sizeof(fpsAvgBuffer), "%2.2f", framerate_avg);
}

void sandboxAddStaticText()
{        
    textBatchRendererAddText("Frametime:      ms", 15.0f, HEIGHT - 40.0f, 0.7f);
    textBatchRendererAddText("FPS:" , 15.0f, HEIGHT - 80.0f, 0.7f);
}

void sandboxCleanUp()
{
    textRenderingSystemsCleanUp();
    objectManagerCleanUp();
    uiCleanUp();
    resourceManagerCleanUp();   
    physicsEngineCleanUp();  
    windowCleanUp();     

    free(dtAccAvgBuffer);
    free(fpsAvgBuffer);
}    