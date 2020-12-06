#ifndef UI
#define UI

#include "../engine-core/window.h"
#include "../engine-core/texture.h"
#include "../engine-core/shader.h"
#include "../engine-core/sprite.h"

// --- Variables ---
#define UI_ELEMENTS 5

static unsigned int* blockTexture, *blockSolidTexture, *pickaxeTexture, *bgTexture, *sbTexture;
static unsigned int* standardShader;
static unsigned int* vertexData;
static Sprite* sprites[UI_ELEMENTS];
static bool elementActive;

// --- Functions ---
void uiInit();
void uiRender();
void uiCleanUp();

static bool uiButtonHover(int* x, int* y, Sprite* sprite);
static int uiGetButtonState(Sprite* sprite);

#endif