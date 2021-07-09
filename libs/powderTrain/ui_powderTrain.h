#ifndef UI_POWDERTRAIN
#define UI_POWDERTRAIN

#include "../engine-core/general/ui.h"
#include "../engine-core/2D/window2D.h"

// --- Variables ---
static unsigned int sbID, sandID, waterID, stoneID, fireID, acidID, woodID;

// --- Functions ---
void uiInit_powderTrain();
int uiGetPressedButton_powderTrain();
bool uiIsMouseInsideMainWindow_powderTrain(double* mouse_x, double* mouse_y);
void uiRender_powderTrain();
void uiAddText_powderTrain();
void uiCleanUp_powderTrain();

#endif