#include "pixelRenderer.h"

void pixelRendererInit(unsigned int width, unsigned int height)
{
    //Create pixel array    
    unsigned char pixelArray[height][width][3];
    int i, j;

    //Initialize pixel array
    for (i = 0; i < height; i++) 
    {
        for (j = 0; j < width; j++)
        {
            if(j < width / 2)
            {
                pixelArray[i][j][0] = 128;
                pixelArray[i][j][1] = 128;
                pixelArray[i][j][2] = 128;
            }
            else
            {
                pixelArray[i][j][0] = 64;
                pixelArray[i][j][1] = 64;
                pixelArray[i][j][2] = 64;
            }            
        }
    }

    //Set some pixels to test texture transformation
    pixelArray[0][0][0] = 255;
    pixelArray[0][0][1] = 255;
    pixelArray[0][0][2] = 0;

    pixelArray[0][width - 1][0] = 255;
    pixelArray[0][width - 1][1] = 255;
    pixelArray[0][width - 1][2] = 0;

    pixelArray[height - 1][0][0] = 255;
    pixelArray[height - 1][0][1] = 255;
    pixelArray[height - 1][0][2] = 0;

    pixelArray[height - 1][width - 1][0] = 255;
    pixelArray[height - 1][width - 1][1] = 255;
    pixelArray[height - 1][width - 1][2] = 0;

    //Generate texture
    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    GLCall(glGenTextures(1, &textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));

    //Configure texture parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelArray));
    
    //Create base sprite with inital texture
    unsigned int spriteData = resourceManagerGetSpriteData();
    unsigned int standardShader = resourceManagerGetShader("standardShader");
    image = createSprite(spriteData, textureID, standardShader, (vec2){0.0f, 0.0f},
                    (vec2){width, height}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);
}

void pixelRendererSet(unsigned int x, unsigned int y, float color[3])
{
    //Manipulate pixel array
}

void pixelRendererFlush()
{
    //Create new texture out of updated pixel array

    //Update sprite texture

    //Render sprite
    renderSprite(image);
}

void pixelRendererCleanUp()
{
    deleteTexture(textureID);
    deleteSprite(image);
}