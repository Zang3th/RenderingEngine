#include "pixelRenderer.h"

void pixelRendererInit(const char* bgImagePath)
{
    //Load background image
    int mode, loadWidth, loadHeight;
    unsigned char* imageLoaded = stbi_load(bgImagePath, &loadWidth, &loadHeight, &mode, 0);
    if(imageLoaded)
    {
        //Save background image twice
        memcpy(&(backgroundImage[0][0][0]), &(imageLoaded[0]), CANVAS_HEIGHT * CANVAS_WIDTH * 3);
        memcpy(&(pixelArray[0][0][0]), &(imageLoaded[0]), CANVAS_HEIGHT * CANVAS_WIDTH * 3);
        log_info("Successfully load background at %s", bgImagePath);
    }
    else
    {   
        log_error("Failed to load background at %s", bgImagePath);
    }    
    stbi_image_free(imageLoaded); //Free resources

    //Generate texture
    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    GLCall(glGenTextures(1, &textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));

    //Configure texture parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    //Create texture out of pixel data
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CANVAS_WIDTH, CANVAS_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelArray));
    
    //Create base sprite with initial background texture
    unsigned int spriteData = resourceManagerGetSpriteData();
    unsigned int standardShader = resourceManagerGetShader("standardShader");
    image = createSprite(spriteData, textureID, standardShader, (vec2){0.0f, 0.0f},
                    (vec2){CANVAS_WIDTH, CANVAS_HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);
}

void pixelRendererSet(unsigned int x, unsigned int y, float color[3])
{
    if(x > 0 && y > 0)
    {
        pixelArray[y - 1][x - 1][0] = color[0] * 255;
        pixelArray[y - 1][x - 1][1] = color[1] * 255;
        pixelArray[y - 1][x - 1][2] = color[2] * 255; 
    }     
}

void pixelRendererReset(unsigned int x, unsigned int y)
{
    if(x > 0 && y > 0)
    {
        pixelArray[y - 1][x - 1][0] = backgroundImage[y - 1][x - 1][0];
        pixelArray[y - 1][x - 1][1] = backgroundImage[y - 1][x - 1][0];
        pixelArray[y - 1][x - 1][2] = backgroundImage[y - 1][x - 1][0];
    }
}

void pixelRendererFlush()
{
    //Create texture out of updated pixel array to update sprite texture
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CANVAS_WIDTH, CANVAS_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelArray));

    //Render sprite
    renderSprite(image);
}

void pixelRendererCleanUp()
{
    deleteTexture(textureID);
    deleteSprite(image);
}