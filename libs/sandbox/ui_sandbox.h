#ifndef UI_SANDBOX
#define UI_SANDBOX

#include "../engine-core/general/ui.h"
#include "objectManager.h"

// --- Variables ---
static unsigned int bgID, sbID, blockID, solidBlockID, bucketID, stickmanID;
extern bool placementMode;

// --- Functions ---
void uiInit_sandbox();
void uiAddText_sandbox();
int uiGetBlockmode_sandbox();
void uiRender_sandbox();
void uiRenderHighlighter_sandbox();
void uiCleanUp_sandbox();

#endif