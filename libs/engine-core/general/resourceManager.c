#include "resourceManager.h"

void resourceManagerLoadTexture(char* name, char* filepath)
{
    if(texCount < MAX_TEXTURES)
    {
        TextureMap temp = {
            name,
            createTexture(filepath)
        };

        texBuffer[texCount] = temp;
        texCount++;
    }
    else
    {
        log_error("Maximum amount of textures allocated!");
    } 
}

void resourceManagerLoadShader(char* name, char* vs_filepath, char* fs_filepath)
{
    if(shaderCount < MAX_SHADER)
    {
        ShaderMap temp = {
            name,
            createShader(vs_filepath, fs_filepath)
        };

        shaderBuffer[shaderCount] = temp;
        shaderCount++;
    }
    else
    {
        log_error("Maximum amount of shaders allocated!");
    } 
}

void resourceManagerLoadSpriteData()
{
    vertexData = createVertexData();
}

unsigned int* resourceManagerGetTexture(char* name)
{
    for(int i = 0; i < texCount; i++)
    {
        if(strcmp(texBuffer[i].texName, name) == 0)
        {
            return texBuffer[i].texture;
        }
    }

    log_error("Couldn't find texture %s", name);
    return NULL;
}

unsigned int* resourceManagerGetShader(char* name)
{
    for(int i = 0; i < shaderCount; i++)
    {   
        if(strcmp(shaderBuffer[i].shaderName, name) == 0)
        {
            return shaderBuffer[i].shader;
        }
    }

    log_error("Couldn't find shader %s", name);
    return NULL;
}

unsigned int* resourceManagerGetSpriteData()
{
    return vertexData;
}

void resourceManagerCleanUp()
{
    //Delete all textures
    for(int i = 0; i < texCount; i++)
    {
        deleteTexture(texBuffer[i].texture);
    }

    //Delete all shaders
    for(int i = 0; i < shaderCount; i++)
    {
        deleteShader(shaderBuffer[i].shader);
    }

    //Delete vertexdata
    if(vertexData != NULL)
        deleteVertexData(vertexData);
}