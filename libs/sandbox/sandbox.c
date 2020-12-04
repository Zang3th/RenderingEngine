#include "sandbox.h"

void sandboxInit()
{
    windowInit();

    //Allocate resources
    cubeTexture = createTexture("res/textures/Block.jpg");
    shader = createShader("res/shader/basic_vs.glsl", "res/shader/basic_fs.glsl");
    spriteData = initSpriteData();    
}

bool sandboxIsRunning()
{        
    return windowIsRunning();
}

void sandboxPerFrame()
{
    windowFrametime();
    windowPrepare();    

    // --- Render
    float velocity = 10.0f * deltaTime;
    lastPos[0] += velocity;
    renderSprite(spriteData, cubeTexture, shader,
                lastPos, (vec2){500.0f, 500.0f},
                45.0f, (vec3){1.0f, 1.0f, 0.0f});

    windowSwapBuffer();
    windowPollEvents();   
}

void sandboxCleanUp()
{
    windowCleanUp();

    deleteTexture(cubeTexture);
    deleteShader(shader);
    deleteSpriteData(spriteData);
}    