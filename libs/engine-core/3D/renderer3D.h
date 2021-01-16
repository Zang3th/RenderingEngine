#ifndef RENDERER3D
#define RENDERER3D

#include <cglm/cglm.h>
#include "../general/sprite.h"
#include "../general/errorManager.h"
#include "../general/shader.h"
#include "../general/texture.h"
#include "../general/vertexArray.h"
#include "../3D/window3D.h"
#include "camera.h"

// --- Variables ---
static mat4 projection;
extern unsigned int drawcalls;

// --- Functions ---
void rendererInit();
void renderSimpleSprite(sprite_t* sprite);

#endif