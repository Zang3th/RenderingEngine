#ifndef SANDBOX
#define SANDBOX

#include "../engine-core/window.h"

// --- Variables ---
static unsigned int* cubeTexture;
static unsigned int* shader;

//--- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandboxCleanUp();

#endif