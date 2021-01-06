#include "textCollector.h"

int textCollectorInit()
{    
    //Init the freetype library
    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        log_error("Couldn't init freetype library!");
        return -1;
    }        
    log_info("Freetype initialized!");

    //Load font as a face as freetype likes to call it
    FT_Face face;
    if(FT_New_Face(ft, "res/fonts/YouAreJustMyType.ttf", 0, &face))
    {
        log_error("Couldn't load font at res/fonts/YouAreJustMyType.ttf");
        return -1;
    }      
    log_info("Successfully load font at res/fonts/YouAreJustMyType.ttf");

    //Set pixel font size
    FT_Set_Pixel_Sizes(face, 0, 48); //Width of 0 lets the face dynamically calculate the width based on the given height

    //Load ascii character set into mapped character buffer
    if(textCollectorRetrieveAsciiSet(face)) //Needs to get copied cause FT_Face is a typedef pointer
    {
        log_error("Failed to retrieve character set!");
        return -1;
    }      
    log_info("Successfully retrieved character set!");

    //Free resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);   

    return 0;
}

int textCollectorRetrieveAsciiSet(FT_Face face)
{
    //Disable byte-alignment restriction cause we're using a single byte per pixel
    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); 
    
    unsigned int character_count = 0;

    for(unsigned char c = 0; c < CHARACTER_SET_SIZE; c++) //hehe c++
    {
        //Load character glyph        
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            log_error("Failed to load glyph: %c", c);
            return -1;
        }       

        //Generate texture
        unsigned int texture;
        GLCall(glGenTextures(1, &texture));
        GLCall(glBindTexture(GL_TEXTURE_2D, texture));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, 
                            face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, 
                            face->glyph->bitmap.buffer));

        //Set texture options
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));   

        //Create character struct
        character_t char_temp;          
        ivec2_t size = {
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows
        };      
        ivec2_t bearing = {
            face->glyph->bitmap_left,
            face->glyph->bitmap_top
        };
        char_temp.textureID = texture;
        memcpy(&char_temp.size, &size, sizeof(ivec2_t));
        memcpy(&char_temp.bearing, &bearing, sizeof(ivec2_t));
        char_temp.advance = face->glyph->advance.x;

        //Map character struct to ascii character and create an entry out of it
        CharacterMap charMap_temp;
        charMap_temp.character = c;

        memcpy(&charMap_temp.characterTexture, &char_temp, sizeof(character_t));

        //Store character texture in array
        memcpy(&charactersMapped[character_count], &charMap_temp, sizeof(CharacterMap));

        //Increment character counter
        character_count++;
    }

    return 0;
}

CharacterMap* textCollectorGetCharacterTexture(char character)
{
    //Iterate over mapped character set
    for(int i = 0; i < CHARACTER_SET_SIZE; i++)
    {
        //Return mapped character entry
        if(charactersMapped[i].character == character)
        {
            return &charactersMapped[i];
            break;
        }            
    }

    log_error("Character couldn't be displayed!");
    log_error("Character %c was not in our character set", character);
    
    return NULL;
}