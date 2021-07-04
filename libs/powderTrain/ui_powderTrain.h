#ifndef UI_SANDBOX
#define UI_SANDBOX

#include "../engine-core/2D/window2D.h"
#include "../engine-core/general/sprite.h"
#include "../engine-core/general/resourceManager.h"
#include "../engine-core/general/renderer.h"
#include "../engine-core/general/textRenderer.h"

// --- Variables ---
#define UI_ELEMENTS 9

static sprite_t* sprites[UI_ELEMENTS];
static sprite_t* highlighter = NULL;
static sprite_t* activeElement = NULL;
static bool elementActive;

// --- Functions ---
void uiInit();
void uiRenderElements();
void uiAddText();
void uiCleanUp();
bool uiButtonHover(int* x, int* y, sprite_t* sprite);
int uiGetButtonState(sprite_t* sprite);
void uiChangeButtonState(sprite_t* sprite, int result, int count);
void uiDeleteButtonPressed();

#endif