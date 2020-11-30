#include "shader.h"

static char* parseShader(const char* filepath)
{
    FILE* fp = fopen(filepath, "r");
    if(!fp)
    {
        log_error("Could not open file: %s", filepath);
        return NULL;
    }

    //to get the size of the file
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, fp);
    fclose(fp);

    log_info("Successfully read shader at %s | size: %d", filepath, fsize);

    string[fsize] = 0;
    return string;
}

static unsigned int compileShader(unsigned int shaderType, const char* source)
{
    GLCall(unsigned int id = glCreateShader(shaderType));
    GLCall(glShaderSource(id, 1, &source, NULL));
    GLCall(glCompileShader(id));

    //Errorhandling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char msg[length];
        GLCall(glGetShaderInfoLog(id, length, &length, msg));
        log_error("Failed to compile %d!", shaderType);
        log_error("%s", msg);
        GLCall(glDeleteShader(id));

        return -1;
    }

    log_info("Successfully compiled shader %d!", shaderType);

    return id;
}

unsigned int* createShader(const char* vsFilepath, const char* fsFilepath)
{    
    //read in shader files
    char* vsSource = parseShader(vsFilepath);
    char* fsSource = parseShader(fsFilepath);
    //log_info("content:\n %s", vsSource);
    //log_info("content:\n %s", fsSource);

    //compile shader
    unsigned int vsID = compileShader(GL_VERTEX_SHADER, vsSource);
    unsigned int fsID = compileShader(GL_FRAGMENT_SHADER, fsSource);

    //free source strings after usage
    free(vsSource);
    free(fsSource);

    //build shader
    unsigned int* shaderID = (unsigned int*)malloc(sizeof(unsigned int));
    //shaderID = buildShader(vsID, fsID);
    
    return shaderID;
}

void deleteShader(unsigned int* shaderID)
{
    free(shaderID);
}