#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include "texture.h"
#include "shader.h"
#include "sprite.h"
#include <string.h>

// --- Variables ---
#define MAX_TEXTURES 16
#define MAX_SHADER 10

typedef struct {
    char* texName;
    unsigned int* texture;
} TextureMap;

typedef struct {
    char* shaderName;
    unsigned int* shader;
} ShaderMap;

static TextureMap texBuffer[MAX_TEXTURES];
static ShaderMap shaderBuffer[MAX_SHADER];
static unsigned int texCount = 0, shaderCount = 0;
static unsigned int* vao = NULL;

// --- Functions ---
void resourceManagerLoadTexture(char* name, char* filepath);
void resourceManagerLoadShader(char* name, char* vs_filepath, char* fs_filepath);
void resourceManagerLoadSpriteData();
unsigned int* resourceManagerGetTexture(char* name);
unsigned int* resourceManagerGetShader(char* name);
unsigned int* resourceManagerGetSpriteData();
void resourceManagerCleanUp();

#endif