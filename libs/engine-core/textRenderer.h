#ifndef TEXTRENDERER
#define TEXTRENDERER

#include "textCollector.h"
#include <cglm/cglm.h>
#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "texture.h"

#define MAX_GLYPH_AMOUNT 100
#define MAX_TEXTURE_AMOUNT 32

// ----- General text rendering system -----
static mat4 projection;

extern unsigned int WIDTH;
extern unsigned int HEIGHT;
extern unsigned int drawcalls;

void textRenderingSystemsInit(unsigned int* batchShader, unsigned int* simpleShader);
void textRenderingSystemsCleanUp();

//Texture caching
typedef struct{
    CharacterMap* characterMap;
    unsigned int textureSlot;
} textureBinding_t;

static textureBinding_t textureCache[MAX_TEXTURE_AMOUNT];
static unsigned int cachedTextures = 0;

// ----- Batch text rendering system ----- 
static unsigned int* batchTextShader = NULL;
static unsigned int* batchTextVAO = NULL, *batchTextVBO = NULL;
static float verticeBuffer[6 * 5 * MAX_GLYPH_AMOUNT];
static unsigned int glyphCount = 0;

void textBatchRendererCreateBuffer();
void textBatchRendererAddText(const char* string, float x, float y, float scale);
textureBinding_t* textBatchRendererCharacterAlreadyCached(char character);
textureBinding_t* textBatchRendererCreateNewCacheEntry(char character);
void textBatchRendererStoreVertices(textureBinding_t* textureCacheEntry, float x, float y, float scale);    
void textBatchRendererUploadToGPU();
void textBatchRendererPrintUsage();
void textBatchRendererDisplay();     

// ----- Simple text rendering system ----- 
static unsigned int* simpleTextShader = NULL;
static unsigned int* simpleTextVAO = NULL, *simpleTextVBO = NULL;

void textSimpleRendererCreateBuffer();
void textSimpleRendererDisplay(const char* text, float x, float y, float scale, vec3 color);

#endif