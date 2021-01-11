#ifndef WRATHGL
#define WRATHGL

#include "../engine-core/3D/window3D.h"
#include "../engine-core/3D/camera.h"

// --- Variables
static camera_t* camera = NULL;

// --- Functions ---
void wrathGLInit();
bool wrathGLIsRunning();
void wrathGLPerFrame();
void wrathGLCleanUp();

#endif