#ifndef SANDBOX
#define SANDBOX

#include "../engine-core/window.h"
#include "../engine-core/texture.h"
#include "../engine-core/shader.h"
#include "../engine-core/sprite.h"
#include <stdlib.h>

// --- Variables ---
static unsigned int* cubeTexture;
static unsigned int* shader;
static unsigned int* spriteData;
static Sprite* spriteStruct;

//--- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandboxCleanUp();

#endif