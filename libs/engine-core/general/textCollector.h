#ifndef TEXTCOLLECTOR
#define TEXTCOLLECTOR

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include "../../../vendor/logging/log.h"
#include "errorManager.h"

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

static CharacterMap charactersMapped[CHARACTER_SET_SIZE];

// --- Functions ---
int textCollectorInit();
int textCollectorRetrieveAsciiSet(FT_Face face);
CharacterMap* textCollectorGetCharacterTexture(char character);

#endif