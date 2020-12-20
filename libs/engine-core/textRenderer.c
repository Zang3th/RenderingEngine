#include "textRenderer.h"

int textRendererInit(unsigned int* shader)
{    
    textShader = shader;

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
    if(textRendererRetrieveAsciiSet(face)) //Needs to get copied cause FT_Face is a typedef pointer
        return -1;  

    //Free resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);    

    //Create projection matrix
    glm_ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f, projection);

    //Create vao and vbo
    textRendererCreateBuffer();
}

int textRendererRetrieveAsciiSet(FT_Face face)
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

        //Store mapped character in array
        memcpy(&characters[character_count], &charMap_temp, sizeof(CharacterMap));

        //Increment character counter
        character_count++;
    }

    return 0;
}

void textRendererCreateBuffer()
{
    textVAO = createVertexArray();
    bindVertexArray(textVAO);
    textVBO = createDynamicVertexBuffer(NULL, sizeof(float) * 6 * 4);
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    unbindVertexBuffer(textVBO);
    unbindVertexArray(textVAO);
}

void textRendererDisplay(const char* text, float x, float y, float scale, vec3 color)
{
    //Set render state
    bindShader(textShader);
    setUniformVec3f(textShader, "textColor", (float*)color);
    setUniformMat4f(textShader, "projection", (float*)projection);
    bindVertexArray(textVAO);

    //Iterate over given text characters
    for(unsigned int i = 0; i < strlen(text); i++)
    {
        //Retrieve character       
        char c = text[i]; 
        character_t* charTexture = NULL;

        //Get corresponding/mapped character texture
        for(unsigned int j = 0; j < CHARACTER_SET_SIZE; j++)
        {   
            if(characters[j].character == c)
            {
                charTexture = &characters[j].characterTexture;
                break;
            }                
        }

        if(!charTexture)
        {
            log_error("Text couldn't be displayed!");
            log_error("Character %c was not in our character set", c);
            break;
        }

        //Calculate values
        float xpos = x + charTexture->bearing.x * scale;
        float ypos = y - (charTexture->size.y - charTexture->bearing.y) * scale;
        float width = charTexture->size.x * scale;
        float height = charTexture->size.y * scale;

        //Update VBO for character
        float vertices[6][4] = {
            { xpos,         ypos + height,  0.0f, 0.0f },            
            { xpos,         ypos,           0.0f, 1.0f },
            { xpos + width, ypos,           1.0f, 1.0f },

            { xpos,         ypos + height,  0.0f, 0.0f },
            { xpos + width, ypos,           1.0f, 1.0f },
            { xpos + width, ypos + height,  1.0f, 0.0f }           
        };

        bindTexture(&charTexture->textureID);
        bindVertexBuffer(textVBO);
        updateDynamicVertexBuffer(vertices, sizeof(vertices));
        unbindVertexBuffer();

        //Render glpyh
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        drawcalls++;

        //Now advance cursor to render next glyph with an offset
        x += (charTexture->advance >> 6) * scale;
    }

    unbindVertexArray();
    unbindTexture();
    unbindShader();
}

void textRendererCleanUp()
{
    deleteVertexArray(textVAO);
    deleteVertexBuffer(textVBO);
}