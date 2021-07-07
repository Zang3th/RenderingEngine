#ifndef UI
#define UI

#include "../2D/window2D.h"
#include "sprite.h"
#include "renderer.h"
#include "textRenderer.h"

// --- Macros ---
#define UI_ELEMENTS_MAX 10

typedef struct{
    sprite_t* sprite;
    int index;
} uiSpriteMap_t;

// --- Variables ---
static sprite_t* ui_Elements[UI_ELEMENTS_MAX];
static uiSpriteMap_t activeElement;
static bool elementActive;
static unsigned int numberOfElements = 0;
static unsigned int trashCanID = 0;
static void (*trashcanCallback)() = NULL;
static float hoverColor[3];

extern sprite_t* highlighter;

// --- Functions ---
void uiInit(float hoverColor[3]);
unsigned int uiAddElement(sprite_t* sprite);
void uiAddHighlighter(sprite_t* sprite);
void uiAddTrashcan(sprite_t* sprite);
void uiRender();
int uiGetPressedButtonID();
sprite_t* uiGetPressedButtonSprite();
bool uiIsButtonPressed(unsigned int index);
bool uiIsButtonHovered(int* x, int* y, unsigned int index);
void uiDefineTrashcanCallback(void (*func));
void uiCleanUp();

#endif