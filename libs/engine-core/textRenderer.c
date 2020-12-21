#include "textRenderer.h"

void textRenderingSystemsInit(unsigned int* batchShader, unsigned int* simpleShader)
{
    //Save shaders for later use
    batchTextShader = batchShader;
    simpleTextShader = simpleShader;

    //Get character set and create textures out of it
    if(textCollectorInit())
        log_error("Something went wrong while collecting the character set");

    //Get character array from the text collector
    textCollectorGetCharacterMap(charArray);

    //Create projection matrix
    glm_ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f, projection);

    //Create vao's and vbo's
    textBatchRendererCreateBuffer();
    textSimpleRendererCreateBuffer();

    //Create uniform texture array for use in the fragment shader
    bindShader(batchTextShader); 
    int samplers[32] = {0, 1, 2, 3, 4, 5, 6 , 7, 8, 9, 10, 11,
                        12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                        22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    setUniform1iv(batchTextShader, "textArray", samplers, MAX_GLYPH_AMOUNT);
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
    //Iterate over given text characters
    for(unsigned int i = 0; i < strlen(text); i++)
    {
        //Retrieve character       
        char c = text[i]; 
        character_t* charTexture = NULL;

        //Get corresponding/mapped character texture
        for(unsigned int j = 0; j < CHARACTER_SET_SIZE; j++)
        {   
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
    batchTextVAO = createVertexArray();
    bindVertexArray(batchTextVAO);
    batchTextVBO = createDynamicVertexBuffer(NULL, sizeof(float) * 6 * 5 * MAX_GLYPH_AMOUNT);
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    defineVertexAttributes(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)16);
    unbindVertexBuffer(batchTextVBO);
    unbindVertexArray(batchTextVAO);
}

void textBatchRendererLoadTextIntoBuffer()
{
    bindVertexBuffer(batchTextVBO);
    updateDynamicVertexBuffer(&verticeBuffer[0], sizeof(float) * 6 * 5 * MAX_GLYPH_AMOUNT);
    unbindVertexBuffer();
    float usageInPercent = ((float)glyphInstanceCount / (float)MAX_GLYPH_AMOUNT) * 100.0f;
    log_info("Batchrenderingsystem: %d out of %d characters used (%2.2f %%)", glyphInstanceCount, MAX_GLYPH_AMOUNT, usageInPercent);
}

void textBatchRendererDisplay()
{
    bindShader(batchTextShader);
    setUniformVec3f(batchTextShader, "textColor", (float*)(vec3){0.8f, 0.8f, 0.8f});
    setUniformMat4f(batchTextShader, "projection", (float*)projection);
    
    bindVertexArray(batchTextVAO);

    for(int i = 0; i < MAX_GLYPH_AMOUNT; i++)
        bindTextureToSlot(&textureIDs[i], i);

    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * glyphInstanceCount));
    drawcalls++;

    unbindTexture();
    unbindVertexArray();     
    unbindShader();
}

void textRenderingSystemsCleanUp()
{
    deleteVertexArray(batchTextVAO);
    deleteVertexBuffer(batchTextVBO);
    deleteVertexArray(simpleTextVAO);
    deleteVertexBuffer(simpleTextVBO);
}

void textSimpleRendererCreateBuffer()
{
    simpleTextVAO = createVertexArray();
    bindVertexArray(simpleTextVAO);
    simpleTextVBO = createDynamicVertexBuffer(NULL, sizeof(float) * 6 * 4);
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    unbindVertexBuffer(simpleTextVBO);
    unbindVertexArray(simpleTextVAO);
}

void textSimpleRendererDisplay(const char* text, float x, float y, float scale, vec3 color)
{
    //Set render state
    bindShader(simpleTextShader);
    setUniformVec3f(simpleTextShader, "textColor", (float*)color);
    setUniformMat4f(simpleTextShader, "projection", (float*)projection);
    bindVertexArray(simpleTextVAO);

    //Iterate over given text characters
    for(unsigned int i = 0; i < strlen(text); i++)
    {
        //Retrieve character       
        char c = text[i]; 
        character_t* charTexture = NULL;

        //Get corresponding/mapped character texture
        for(unsigned int j = 0; j < CHARACTER_SET_SIZE; j++)
        {   
            if(charArray[j].character == c)
            {
                charTexture = &charArray[j].characterTexture;
                break;
            }                
        }

        if(!charTexture)
        {
            log_error("Text couldn't be displayed!");
            log_error("Character %c was not in our character set", text[i]);
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
        bindVertexBuffer(simpleTextVBO);
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