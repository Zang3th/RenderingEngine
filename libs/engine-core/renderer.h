#ifndef RENDERER
#define RENDERER

#include "sprite.h"
#include "errorManager.h"

// --- Variables ---
static mat4 projection;
extern int drawCalls;

// --- Functions ---
void rendererInit();
void renderSimpleSprite(Sprite* sprite);

#endif