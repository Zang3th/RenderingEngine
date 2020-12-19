#include "textRenderer.h"

int textRendererInit()
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
    if(textRendererRetrieveAsciiSet(&face))
        return -1;
}

int textRendererRetrieveAsciiSet(FT_Face* face)
{
    //Disable byte-alignment restriction cause we're using a single byte per pixel
    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); 

    for(unsigned char c = 0; c < CHARACTER_SET_SIZE; c++) //hehe c++
    {
        //Load character glyph        
        if(FT_Load_Char(*face, c, FT_LOAD_RENDER))
        {
            log_error("Failed to load glyph: %c", c);
            return -1;
        }       

        //Generate texture
        unsigned int texture;
        GLCall(glGenTextures(1, &texture));
        GLCall(glBindTexture(GL_TEXTURE_2D, texture));
    }
}