#ifndef SANDBOX
#define SANDBOX

#include "ui.h"

// --- Functions ---
void sandboxInit();
bool sandboxIsRunning();
void sandboxPerFrame();
void sandboxCleanUp();

#endif