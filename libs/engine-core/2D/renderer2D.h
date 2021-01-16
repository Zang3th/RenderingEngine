#ifndef RENDERER2D
#define RENDERER2D

#include "../general/sprite.h"
#include "../general/errorManager.h"
#include "../../sandbox/objectInstancer.h"
#include "../general/shader.h"
#include "../general/texture.h"
#include "../general/vertexArray.h"
#include "../2D/window2D.h"

// --- Variables ---
static mat4 projection;
extern unsigned int drawcalls;

// --- Functions ---
void rendererInit();
void renderSimpleSprite(sprite_t* sprite);
void renderInstancedSprite(instance_t* instance);

#endif