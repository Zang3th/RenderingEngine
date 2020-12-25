#include "textRenderer.h"

void textRenderingSystemsInit(unsigned int* batchShader, unsigned int* simpleShader)
{
    //Save shaders for later use
    batchTextShader = batchShader;
    simpleTextShader = simpleShader;

    //Get character set and create textures out of it
    if(textCollectorInit())
        log_error("Something went wrong while collecting the character set");

    //Create projection matrix
    glm_ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f, projection);

    //Create vao's and vbo's
    textBatchRendererCreateBuffer();
    textSimpleRendererCreateBuffer();

    //Create uniform texture array for indexing cached textures
    bindShader(batchTextShader); 
    int texSlotSamplers[MAX_TEXTURE_AMOUNT] = {  0, 1, 2, 3, 4, 5, 6 , 7, 8, 9, 10, 11,
                                                12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                                                22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    setUniform1iv(batchTextShader, "textArray", texSlotSamplers, MAX_TEXTURE_AMOUNT);
}

void textBatchRendererAddText(const char* string, float x, float y, float scale)
{  
    //Iterate over every character in the given string
    for(unsigned int i = 0; i < strlen(string); i++)
    {
        //Check if we still got place to render the glyph
        if(glyphCount < MAX_GLYPH_AMOUNT)
        {
            //Get current string character
            char currentCharacter = string[i];

            //Check if current character got already cached
            textureBinding_t* textureCacheEntry = textBatchRendererCharacterAlreadyCached(currentCharacter);
            
            //If we got no cache entry
            if(textureCacheEntry == NULL)
            {
                //Check if we still got open cache slots
                if(cachedTextures < MAX_TEXTURE_AMOUNT)            
                    textureCacheEntry = textBatchRendererCreateNewCacheEntry(currentCharacter); //Create new cache entry
                else
                {
                    log_warn("Batchrendering: Maximum amount of glyph textures cached. Please use the already cached glyphs!");
                    break;      
                }
            }

            //Create and store character vertices (includes the texture)  
            textBatchRendererStoreVertices(textureCacheEntry, x, y, scale);

            //Advance cursor to render next glyph with an offset
            x += (textureCacheEntry->characterMap->characterTexture.advance >> 6) * scale;
        }
        else
        {
            log_warn("Maximum amount of glyphs rendered. Increase the maximum or write less text!");
        }        
    }     
}

textureBinding_t* textBatchRendererCharacterAlreadyCached(char character)
{
    //Go through all cached textures and check if given character got already stored
    for(unsigned int i = 0; i < cachedTextures; i++)
    {
        if(textureCache[i].characterMap->character == character)
            return &textureCache[i];
    }

    return NULL;
}

textureBinding_t* textBatchRendererCreateNewCacheEntry(char character)
{   
    //Get corresponding/mapped character texture from the charArray out of the textCollector
    CharacterMap* charMap = textCollectorGetCharacterTexture(character);

    if(charMap != NULL)
    {
        //Create texture cache entry
        textureBinding_t temp;
        temp.characterMap = charMap;
        temp.textureSlot = cachedTextures;
        unsigned int textureID = charMap->characterTexture.textureID;
        unsigned int insertPoint = cachedTextures;
        memcpy(&textureCache[insertPoint], &temp, sizeof(textureBinding_t));

        //Increment texture cache counter
        cachedTextures++;

        return &textureCache[insertPoint];
    }

    return NULL;
}

void textBatchRendererStoreVertices(textureBinding_t* textureCacheEntry, float x, float y, float scale)
{   
    //Character texture
    character_t charTex = textureCacheEntry->characterMap->characterTexture;
    
    //Calculate values
    float xpos = x + charTex.bearing.x * scale;
    float ypos = y - (charTex.size.y - charTex.bearing.y) * scale;
    float width = charTex.size.x * scale;
    float height = charTex.size.y * scale;

    float texSlot = (float)textureCacheEntry->textureSlot;

    //Create vertice data for character
    float vertices[6][5] = {
        { xpos,         ypos + height,  0.0f, 0.0f, texSlot },            
        { xpos,         ypos,           0.0f, 1.0f, texSlot },
        { xpos + width, ypos,           1.0f, 1.0f, texSlot },

        { xpos,         ypos + height,  0.0f, 0.0f, texSlot },
        { xpos + width, ypos,           1.0f, 1.0f, texSlot },
        { xpos + width, ypos + height,  1.0f, 0.0f, texSlot }           
    };
    
    //Save glyphvertices in vertice data buffer
    memcpy(&verticeBuffer[glyphCount * 6 * 5], vertices, sizeof(float) * 6 * 5);

    glyphCount++;
}

void textBatchRendererCreateBuffer()
{
    //Create vao
    batchTextVAO = createVertexArray();
    bindVertexArray(batchTextVAO);

    //Create vbo
    batchTextVBO = createDynamicVertexBuffer(NULL, sizeof(float) * 6 * 5 * MAX_GLYPH_AMOUNT);

    //Configure vertex layout
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    defineVertexAttributes(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)16);

    //Unbind vao and vbo
    unbindVertexBuffer(batchTextVBO);
    unbindVertexArray(batchTextVAO);
}

void textBatchRendererUploadToGPU()
{
    bindVertexBuffer(batchTextVBO);
    updateDynamicVertexBuffer(&verticeBuffer[0], sizeof(float) * 6 * 5 * MAX_GLYPH_AMOUNT);
    unbindVertexBuffer();

    textBatchRendererPrintUsage();
}

void textBatchRendererPrintUsage()
{
    float texUsageInPercent = ((float)cachedTextures / (float)MAX_TEXTURE_AMOUNT) * 100.0f;
    float charUsageInPercent = ((float)glyphCount / (float)MAX_GLYPH_AMOUNT) * 100.0f;

    log_info("Batchrendering: %d characters printed. %d are max. possible (%2.2f %%)", glyphCount, MAX_GLYPH_AMOUNT, charUsageInPercent);
    log_info("Batchrendering: %d out of %d glyph texture slots used (%2.2f %%)", cachedTextures, MAX_TEXTURE_AMOUNT, texUsageInPercent);   
}

void textBatchRendererDisplay()
{
    bindShader(batchTextShader);
    setUniformVec3f(batchTextShader, "textColor", (float*)(vec3){0.8f, 0.8f, 0.8f});
    setUniformMat4f(batchTextShader, "projection", (float*)projection);
    
    bindVertexArray(batchTextVAO);

    //Bind textures
    for(int i = 0; i < cachedTextures; i++)   
        bindTextureToSlot(&textureCache[i].characterMap->characterTexture.textureID, i);          

    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * glyphCount));
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

        //Get corresponding/mapped character texture from the charArray out of the textCollector
        CharacterMap* charMap = textCollectorGetCharacterTexture(c);

        //Calculate values
        float xpos = x + charMap->characterTexture.bearing.x * scale;
        float ypos = y - (charMap->characterTexture.size.y - charMap->characterTexture.bearing.y) * scale;
        float width = charMap->characterTexture.size.x * scale;
        float height = charMap->characterTexture.size.y * scale;

        //Update VBO for character
        float vertices[6][4] = {
            { xpos,         ypos + height,  0.0f, 0.0f },            
            { xpos,         ypos,           0.0f, 1.0f },
            { xpos + width, ypos,           1.0f, 1.0f },

            { xpos,         ypos + height,  0.0f, 0.0f },
            { xpos + width, ypos,           1.0f, 1.0f },
            { xpos + width, ypos + height,  1.0f, 0.0f }           
        };

        bindTexture(&charMap->characterTexture.textureID);
        bindVertexBuffer(simpleTextVBO);
        updateDynamicVertexBuffer(vertices, sizeof(vertices));
        unbindVertexBuffer();

        //Render glpyh
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        drawcalls++;

        //Now advance cursor to render next glyph with an offset
        x += (charMap->characterTexture.advance >> 6) * scale;
    }

    unbindVertexArray();
    unbindTexture();
    unbindShader();
}