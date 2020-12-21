#ifndef TEXTRENDERER
#define TEXTRENDERER

#include "textCollector.h"
#include <cglm/cglm.h>
#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "texture.h"

// --- Variables ---
#define MAX_GLYPH_AMOUNT 32

static unsigned int* textShader = NULL;
static mat4 projection;
static unsigned int* textVAO = NULL, *textVBO = NULL;
static float verticeBuffer[6 * 5 * MAX_GLYPH_AMOUNT];
static unsigned int glyphInstanceCount = 0;
static unsigned int textureIDs[MAX_GLYPH_AMOUNT];

extern unsigned int WIDTH;
extern unsigned int HEIGHT;
extern unsigned int drawcalls;

// --- Functions ---
void textBatchRendererInit(unsigned int* shader);
void textBatchRendererAddText(const char* text, float x, float y, float scale);
void textBatchRendererCreateVertices(const char* text, float x, float y, float scale);
void textBatchRendererCreateBuffer();
void textBatchRendererLoadTextIntoBuffer();
void textBatchRendererDisplay();
void textBatchRendererCleanUp();

#endif