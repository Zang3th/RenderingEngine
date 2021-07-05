#ifndef UI
#define UI

#include "../2D/window2D.h"
#include "sprite.h"
#include "renderer.h"
#include "textRenderer.h"

// --- Macros ---
#define UI_ELEMENTS_MAX 10

// --- Variables ---
static sprite_t* ui_Elements[UI_ELEMENTS_MAX];
static sprite_t* highlighter = NULL;
static sprite_t* activeElement = NULL;
static unsigned int numberOfElements = 0;
static unsigned int trashCanID = 0;

// --- Functions ---
void uiInit();
void uiAddElement(sprite_t* sprite);
void uiAddHighlighter(sprite_t* sprite);
void uiAddTrashcan(sprite_t* sprite);
void uiRender();
void uiCleanUp();
sprite_t* uiGetPressedButton();

#endif