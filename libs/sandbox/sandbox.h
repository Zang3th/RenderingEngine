#ifndef SANDBOX
#define SANDBOX

#include "../engine-core/window.h"

//--- Functions ---
void sandboxInit();

bool sandboxIsRunning();

void sandboxPerFrame();

void sandboxCleanUp();

#endif