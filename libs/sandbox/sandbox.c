#include "sandbox.h"
#include "../engine-core/texture.h"
#include "../engine-core/shader.h"

void sandboxInit()
{
    windowInit();

    cubeTexture = createTexture("res/textures/Block.jpg");
    bindTexture(cubeTexture);

    shader = createShader("res/shader/basic_vs.glsl", "res/shader/basic_fs.glsl");
    bindShader(shader);
}

bool sandboxIsRunning()
{        
    return windowIsRunning();
}

void sandboxPerFrame()
{
    windowPollEvents();
    windowRender();
}

void sandboxCleanUp()
{
    windowCleanUp();
    deleteTexture(cubeTexture);
    deleteShader(shader);
}    