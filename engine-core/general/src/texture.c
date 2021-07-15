#include "texture.h"

unsigned int createTexture(const char* path)
{
    int width, height, BPP; 
    unsigned int textureID;
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
            return -1;
        }            

        GLCall(glGenTextures(1, &textureID));
        bindTexture(textureID);

        //Texture parameters
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        //Activate anisotropic filtering
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0));
        GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f));

        log_info("Successfully load texture at %s", path);
        stbi_image_free(localBuffer);

        return textureID;
    }
    else
    {
        log_error("Failed to load texture at %s", path);
        stbi_image_free(localBuffer);

        return -2;
    }
}

void deleteTexture(unsigned int textureID)
{
    GLCall(glDeleteTextures(1, &textureID));
}

void bindTexture(unsigned int textureID)
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
}

void bindTextureToSlot(unsigned int textureID, unsigned int slot)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
}

void unbindTexture()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}