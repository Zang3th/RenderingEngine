#include "textRenderer.h"

void textBatchRendererInit(unsigned int* shader)
{
    //Save shader for late use
    textShader = shader;

    //Get character set and create textures out of it
    if(textCollectorInit())
        log_error("Something went wrong while collecting the character set");

    //Create projection matrix
    glm_ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f, projection);

    //Create vao and vbo
    textBatchRendererCreateBuffer();

    //Create uniform texture array for use in the fragment shader
    bindShader(textShader); 
    int samplers[32] = {0, 1, 2, 3, 4, 5, 6 , 7, 8, 9, 10, 11,
                        12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                        22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    glUniform1iv(glGetUniformLocation(*textShader, "textArray"), 32, samplers);
}

void textBatchRendererAddText(const char* text, float x, float y, float scale)
{
    //Check if there are still open texture slots to save new glyphs
    if(glyphInstanceCount < MAX_GLYPH_AMOUNT)
        textBatchRendererCreateVertices(text, x, y, scale);
    else
    {
        log_warn("Batchrenderingsystem is full. Text: '%s' wasn't added!", text);
        log_warn("Please remember to keep yourself to max. 32 characters");
        log_warn("or use an additional batchrenderingsystem!");
    }
}

void textBatchRendererCreateVertices(const char* text, float x, float y, float scale)
{
    //Get character array from the text collector
    CharacterMap charArray[CHARACTER_SET_SIZE];
    textCollectorGetCharacterMap(charArray);

    //Iterate over given text characters
    for(unsigned int i = 0; i < strlen(text); i++)
    {
        //Retrieve character       
        char c = text[i]; 
        character_t* charTexture = NULL;

        //Get corresponding/mapped character texture
        for(unsigned int j = 0; j < CHARACTER_SET_SIZE; j++)
        {   
            //log_info("%c", characters[j].character);
            if(charArray[j].character == c)
            {
                charTexture = &charArray[j].characterTexture;
                break;
            }                
        }

        //Save current glyph texture id in textures array
        textureIDs[glyphInstanceCount] = charTexture->textureID;

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

        float texCount = (float)glyphInstanceCount;

        //Create vertice data for character
        float vertices[6][5] = {
            { xpos,         ypos + height,  0.0f, 0.0f, texCount },            
            { xpos,         ypos,           0.0f, 1.0f, texCount },
            { xpos + width, ypos,           1.0f, 1.0f, texCount },

            { xpos,         ypos + height,  0.0f, 0.0f, texCount },
            { xpos + width, ypos,           1.0f, 1.0f, texCount },
            { xpos + width, ypos + height,  1.0f, 0.0f, texCount }           
        };

        //Now advance cursor to render next glyph with an offset
        x += (charTexture->advance >> 6) * scale;
        
        //Save glyphvertices in vertice data buffer
        memcpy(&verticeBuffer[glyphInstanceCount * 6 * 5], vertices, sizeof(float) * 6 * 5);
        glyphInstanceCount++;
    }
}

void textBatchRendererCreateBuffer()
{
    textVAO = createVertexArray();
    bindVertexArray(textVAO);
    textVBO = createDynamicVertexBuffer(NULL, sizeof(float) * 6 * 5 * MAX_GLYPH_AMOUNT);
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    defineVertexAttributes(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)16);
    unbindVertexBuffer(textVBO);
    unbindVertexArray(textVAO);
}

void textBatchRendererLoadTextIntoBuffer()
{
    bindVertexBuffer(textVBO);
    updateDynamicVertexBuffer(&verticeBuffer[0], sizeof(float) * 6 * 5 * MAX_GLYPH_AMOUNT);
    unbindVertexBuffer();
    float usageInPercent = ((float)glyphInstanceCount / (float)MAX_GLYPH_AMOUNT) * 100.0f;
    log_info("Batchrenderingsystem: %d out of %d characters used (%2.2f %%)", glyphInstanceCount, MAX_GLYPH_AMOUNT, usageInPercent);
}

void textBatchRendererDisplay()
{
    bindShader(textShader);
    setUniformVec3f(textShader, "textColor", (float*)(vec3){1.0f, 1.0f, 1.0f});
    setUniformMat4f(textShader, "projection", (float*)projection);
    
    bindVertexArray(textVAO);

    for(int i = 0; i < MAX_GLYPH_AMOUNT; i++)
        bindTextureToSlot(&textureIDs[i], i);

    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * glyphInstanceCount));
    drawcalls++;

    unbindTexture();
    unbindVertexArray();     
    unbindShader();
}

void textBatchRendererCleanUp()
{
    deleteVertexArray(textVAO);
    deleteVertexBuffer(textVBO);
}