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
    resourceManagerLoadShader("batchTextShader", "res/shader/batchText_vs.glsl", "res/shader/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "res/shader/simpleText_vs.glsl", "res/shader/simpleText_fs.glsl");
    resourceManagerLoadSpriteData();   

    //Init modules that depend on resources
    uiInit();  
    objectManagerInit();   

    //Allocate memory for monitoring buffer
    dtAccAvgBuffer = malloc(sizeof(float));
    fpsAvgBuffer = malloc(sizeof(float));

    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 characters!
        textRenderingSystemsInit(resourceManagerGetShader("batchTextShader"), resourceManagerGetShader("simpleTextShader"));

        //Add text
        uiAddText();
        sandboxAddStaticText();        

        //After all text got added -> create one big buffer out of it, to render everything in 1 drawcall
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

    // --- Do render
        // -- Reset drawCall counter for current frame
        drawcalls = 0; 
        uiRenderElements();    

        objectManagerCheckForPlacement();
        objectManagerRenderObjects();    

        uiRenderHighlighter(); 

        //sandboxRenderText();  
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
    windowCleanUp();     

    free(dtAccAvgBuffer);
    free(fpsAvgBuffer);
}    