#ifndef RENDERER
#define RENDERER

#include "sprite.h"
#include "errorManager.h"
#include "../sandbox/objectInstancer.h"
#include "shader.h"
#include "texture.h"
#include "vertexArray.h"

// --- Variables ---
static mat4 projection;
extern unsigned int drawcalls;

// --- Functions ---
void rendererInit();
void renderSimpleSprite(sprite_t* sprite);
void renderInstancedSprite(instance_t* instance);

#endif