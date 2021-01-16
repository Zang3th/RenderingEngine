#include "wrathGL.h"

void wrathGLInit()
{
    //Init modules
    windowInit();   
    rendererInit();

    //Load resources
    resourceManagerLoadTexture("blockTexture", "res/textures/sandbox/Block.jpg");       
    resourceManagerLoadShader("objectShader", "res/shader/wrathGL/object_vs.glsl", "res/shader/wrathGL/object_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "res/shader/sandbox/batchText_vs.glsl", "res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "res/shader/sandbox/simpleText_vs.glsl", "res/shader/sandbox/simpleText_fs.glsl");
    resourceManagerLoadSpriteData();

    //Get resources
    unsigned int* blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int* objectShader = resourceManagerGetShader("objectShader");
    unsigned int* spriteData = resourceManagerGetSpriteData();

    //Create Sprite
    testSprite = createSprite
    (
        spriteData, blockTexture, objectShader, (vec2){800.0f, 450.0f},
        (vec2){200.0f, 200.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false
    );

    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 different characters!
        textRenderingSystemsInit(resourceManagerGetShader("batchTextShader"), resourceManagerGetShader("simpleTextShader"));
        monitoringInit();  

        //Add static text
        monitoringAddText();

        //After all text got added -> create one big buffer out of it, to render all batched text in one drawcall
        textBatchRendererUploadToGPU(); 
}

bool wrathGLIsRunning()
{
    return windowIsRunning();
}

void wrathGLPerFrame()
{
    // --- Pre render
        windowCalcFrametime();
        windowPollEvents();
        windowProcessEvents();
        windowPrepare();         

    // --- Do render
        // -- Reset drawCall counter for current frame
        drawcalls = 0; 
        renderSimpleSprite(testSprite);

        GLCall(glDisable(GL_DEPTH_TEST));
        textBatchRendererDisplay(); 
        monitoringRenderText(deltaTime);
        GLCall(glEnable(GL_DEPTH_TEST));

    // --- After render
        windowUpdateTitle(drawcalls);

        windowSwapBuffer(); 
}

void wrathGLCleanUp()
{
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    resourceManagerCleanUp(); 
    deleteSprite(testSprite);
    windowCleanUp(); 
}