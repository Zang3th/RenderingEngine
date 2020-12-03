#include "texture.h"

unsigned int* createTexture(const char* path)
{
    int width, height, BPP; 
    unsigned int* rendererID = (unsigned int*)malloc(sizeof(unsigned int));
    stbi_set_flip_vertically_on_load(1);
    unsigned char* localBuffer = stbi_load(path, &width, &height, &BPP, 0);

    if(localBuffer)
    {
        GLenum format;
        if(BPP == 1)
            format = GL_RED;
        else if(BPP == 3)
            format = GL_RGB;
        else if(BPP == 4)
            format = GL_RGBA;
        else
        {
            log_error("Imageformat is not supported!");
            return NULL;
        }            

        GLCall(glGenTextures(1, rendererID));
        bindTexture(rendererID);
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer));

        log_info("Successfully load texture at %s", path);
        stbi_image_free(localBuffer);

        return rendererID;
    }
    else
    {
        log_error("Failed to load texture at %s", path);
        stbi_image_free(localBuffer);

        return NULL;
    }
}

void deleteTexture(unsigned int* textureID)
{
    GLCall(glDeleteTextures(1, textureID));
    free(textureID);
}

void bindTexture(const unsigned int* textureID)
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, *textureID));
}

void unbindTexture()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}