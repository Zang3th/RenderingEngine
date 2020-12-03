#include "sandbox.h"

void sandboxInit()
{
    windowInit();

    //Allocate resources
    cubeTexture = createTexture("res/textures/Block.jpg");
    shader = createShader("res/shader/basic_vs.glsl", "res/shader/basic_fs.glsl");

    spriteData = initSpriteData();

    spriteStruct = (Sprite*)malloc(sizeof(Sprite));
    *(spriteStruct->position) = (1.0f, 1.0f);
    *(spriteStruct->size) = (1.0f, 1.0f);
    spriteStruct->rotation = 0.0f;
    *(spriteStruct->color) = (1.0f, 0.0f, 0.0f);
}

bool sandboxIsRunning()
{        
    return windowIsRunning();
}

void sandboxPerFrame()
{
    windowPollEvents();
    windowRender();
    renderSprite(spriteData, cubeTexture, shader, spriteStruct);
}

void sandboxCleanUp()
{
    windowCleanUp();

    deleteTexture(cubeTexture);
    deleteShader(shader);
    deleteSpriteData(spriteData);
    free(spriteStruct);
}    