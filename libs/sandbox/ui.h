#ifndef UI
#define UI

#include "../engine-core/window.h"
#include "../engine-core/sprite.h"
#include "../engine-core/resourceManager.h"
#include "../engine-core/renderer.h"

// --- Variables ---
#define UI_ELEMENTS 5

static Sprite* sprites[UI_ELEMENTS];
static bool elementActive;

// --- Functions ---
void uiInit();
void uiRender();
void uiCleanUp();

static bool uiButtonHover(int* x, int* y, Sprite* sprite);
static int uiGetButtonState(Sprite* sprite);

#endif