#ifndef TEXTRENDERER
#define TEXTRENDERER

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include "../../vendor/logging/log.h"
#include "errorManager.h"
#include "shader.h"
#include <cglm/cglm.h>
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "texture.h"

// --- Variables ---
#define CHARACTER_SET_SIZE 128

typedef struct{
    int x;
    int y;
} ivec2_t;

typedef struct{
    unsigned int textureID; //Handle of the glyph texture
    ivec2_t size;           //Size of the glyph
    ivec2_t bearing;        //Offset from the baseline to left/top of the glyph
    unsigned int advance;   //Offset to advance to next glyph
} character_t;

typedef struct{
    char character;
    character_t characterTexture;
} CharacterMap;

static unsigned int* textShader = NULL;
static CharacterMap characters[CHARACTER_SET_SIZE];
static mat4 projection;
static unsigned int* textVAO = NULL, *textVBO = NULL;

extern unsigned int WIDTH;
extern unsigned int HEIGHT;
extern unsigned int drawcalls;

// --- Functions ---
int textRendererInit(unsigned int* shader);
int textRendererRetrieveAsciiSet(FT_Face face);
void textRendererCreateBuffer();
void textRendererDisplay(const char* text, float x, float y, float scale, vec3 color);
void textRendererCleanUp();

#endif