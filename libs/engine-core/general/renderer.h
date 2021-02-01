#ifndef RENDERER
#define RENDERER

#include <cglm/cglm.h>
#include "errorManager.h"
#include "shader.h"
#include "texture.h"
#include "vertexArray.h"
#include "camera.h"
#include "sprite.h"
#include "objectInstancer.h"
#include "model.h"

// --- Variables ---
static mat4 perspectiveProj, orthoProj;
static camera_t* rendererCamera;
extern unsigned int drawcalls;
extern unsigned int vertices;

// --- Functions ---
void rendererInit(camera_t* camera);
void renderSprite(sprite_t* sprite);
void renderInstancedSprite(instance_t* instance);
void renderModel(model_t* model);

#endif