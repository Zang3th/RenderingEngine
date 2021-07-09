#ifndef WINDOW2D
#define WINDOW2D

#include "../general/window.h"

// --- Functions ---
void window2DInit(char* title);
bool window2DIsRunning();
void window2DPollEvents();
void window2DPrepare();
void window2DSwapBuffer();
void window2DCleanUp();
void window2DCalcFrametime();
void window2DGetMousePos(double* x, double* y);
void window2DSetMousePos(double x, double y);
void window2DUpdateTitle(int drawcalls);
void window2DPrepareDrawcallBuffer(int drawcalls);

#endif