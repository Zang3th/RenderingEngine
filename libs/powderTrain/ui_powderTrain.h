#ifndef UI_POWDERTRAIN
#define UI_POWDERTRAIN

#include "../engine-core/general/ui.h"

// --- Variables ---
static unsigned int sbID, sandID, waterID, stoneID, fireID, acidID, woodID;

// --- Functions ---
void uiInit_powderTrain();
void uiRender_powderTrain();
void uiAddText_powderTrain();
void uiCleanUp_powderTrain();

#endif