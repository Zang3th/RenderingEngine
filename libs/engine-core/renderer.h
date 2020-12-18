#ifndef RENDERER
#define RENDERER

#include "sprite.h"
#include "errorManager.h"
#include "../sandbox/objectInstancer.h"

// --- Variables ---
static mat4 projection;
extern int drawCalls;

// --- Functions ---
void rendererInit();
void renderSimpleSprite(Sprite* sprite);
void renderInstancedSprite(ObjInstance* instance);

#endif