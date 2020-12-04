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
        log_error("Failed to compile shader %d!", shaderType);
        log_error("%s", msg);
        GLCall(glDeleteShader(id));

        return -1;
    }

    log_info("Successfully compiled shader %d!", shaderType);

    return id;
}

static unsigned int buildShader(unsigned int vsID, unsigned int fsID)
{
    GLCall(unsigned int programID = glCreateProgram());
    GLCall(glAttachShader(programID, vsID));
    GLCall(glAttachShader(programID, fsID));
    GLCall(glLinkProgram(programID));

    //Errorhandling
    int result;
    GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &result));
    if(!result)
    {
        int length;
        GLCall(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length));
        char msg[length];
        GLCall(glGetProgramInfoLog(programID, length, &length, msg));
        log_error("Failed to link shader!");
        log_error("%s", msg);
        GLCall(glDeleteProgram(programID));

        return -1;
    }

    GLCall(glValidateProgram(programID));

    log_info("Successfully linked shader! (program: %d)", programID);

    //Free shader
	GLCall(glDetachShader(programID, vsID));
	GLCall(glDetachShader(programID, fsID));
	GLCall(glDeleteShader(vsID));
	GLCall(glDeleteShader(fsID));

    return programID;
}

unsigned int* createShader(const char* vsFilepath, const char* fsFilepath)
{    
    //Read in shader files
    char* vsSource = parseShader(vsFilepath);
    char* fsSource = parseShader(fsFilepath);

    //Compile shader
    unsigned int vsID = compileShader(GL_VERTEX_SHADER, vsSource);
    unsigned int fsID = compileShader(GL_FRAGMENT_SHADER, fsSource);

    //Free source strings after usage
    free(vsSource);
    free(fsSource);

    //Build shader
    unsigned int* shaderID = (unsigned int*)malloc(sizeof(unsigned int));
    *shaderID = buildShader(vsID, fsID);
    
    return shaderID;
}

void deleteShader(unsigned int* shaderID)
{
    free(shaderID);
}

void bindShader(const unsigned int* shaderID)
{
    GLCall(glUseProgram(*shaderID));
}

void unbindShader()
{
    GLCall(glUseProgram(0));
}

void setUniform1i(const unsigned int* shaderID, const char* name, int value)
{
    GLCall(int location = glGetUniformLocation(*shaderID, name));
    GLCall(glUniform1i(location, value));
}

void setUniform1f(const unsigned int* shaderID, const char* name, float value)
{
    GLCall(int location = glGetUniformLocation(*shaderID, name));
    GLCall(glUniform1f(location, value));
}

void setUniform4f(const unsigned int* shaderID, const char* name, float v0, float v1, float v2, float v3)
{
    GLCall(int location = glGetUniformLocation(*shaderID, name));
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void setUniformMat4f(const unsigned int* shaderID, const char* name, float* matrix)
{
    GLCall(int location = glGetUniformLocation(*shaderID, name));
    GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, matrix)); //<cglm> documentation recommends this
}

void setUniformVec3f(const unsigned int* shaderID, const char* name, float* vector)
{
    GLCall(int location = glGetUniformLocation(*shaderID, name));
    GLCall(glUniform3fv(location, 1, (float*)vector));
}