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

    //General
    static mat4 projection;
    static CharacterMap charArray[CHARACTER_SET_SIZE];

    extern unsigned int WIDTH;
    extern unsigned int HEIGHT;
    extern unsigned int drawcalls;

    //Batch
    static unsigned int* batchTextShader = NULL;
    static unsigned int* batchTextVAO = NULL, *batchTextVBO = NULL;
    static float verticeBuffer[6 * 5 * MAX_GLYPH_AMOUNT];
    static unsigned int glyphInstanceCount = 0;
    static unsigned int textureIDs[MAX_GLYPH_AMOUNT];

    //Simple
    static unsigned int* simpleTextShader = NULL;
    static unsigned int* simpleTextVAO = NULL, *simpleTextVBO = NULL;

// --- Functions ---
    //General
    void textRenderingSystemsInit(unsigned int* batchShader, unsigned int* simpleShader);
    void textRenderingSystemsCleanUp();

    //Batch
    void textBatchRendererAddText(const char* text, float x, float y, float scale);
    void textBatchRendererCreateVertices(const char* text, float x, float y, float scale);
    void textBatchRendererCreateBuffer();
    void textBatchRendererLoadTextIntoBuffer();
    void textBatchRendererDisplay();    

    //Simple
    void textSimpleRendererCreateBuffer();
    void textSimpleRendererDisplay(const char* text, float x, float y, float scale, vec3 color);

#endif