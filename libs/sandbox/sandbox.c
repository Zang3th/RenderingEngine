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
    windowPrepare();

    renderSprite(spriteData, cubeTexture, shader, (vec3){1.0f, 1.0f, 1.0f});

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