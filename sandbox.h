#ifndef SANDBOX
#define SANDBOX

#include "window.h"

//--- Functions ---
void sandboxInit();

bool sandboxIsRunning();

void sandboxPerFrame();

void sandboxCleanUp();

#endif