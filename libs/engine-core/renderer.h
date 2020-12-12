#ifndef RENDERER
#define RENDERER

#include "sprite.h"
#include "errorManager.h"

// --- Variables ---
static mat4 projection;

// --- Functions ---
void rendererInit();
void renderSimpleSprite(Sprite* sprite);

#endif