#ifndef WINDOW3D
#define WINDOW3D

#include "../../general/include/window.h"
#include "../../general/include/camera.h"

// --- Variables ---
static bool windowInFocus = false;

extern camera_t* camera;
extern bool wireframeMode;
extern bool generateNewTerrain;

// --- Functions ---
void window3DInit(char* title);
bool window3DIsRunning();
void window3DPollEvents();
void window3DPrepare();
void window3DSwapBuffer();
void window3DCleanUp();
void window3DCalcFrametime();
void window3DGetMousePos(double* x, double* y);
void window3DUpdateTitle(int drawcalls);
void window3DPrepareDrawcallBuffer(int drawcalls);

#endif