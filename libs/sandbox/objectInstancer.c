#include "objectInstancer.h"

ObjInstance* objectInstancerCreateInstance(unsigned int* texture, float* color)
{
    //Create and bind vao
    unsigned int* vao = createVertexArray();
    bindVertexArray(vao);

    //Create data
    float vertices[] =
    {
        //Position  //Texture
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    //Create model buffer and set it to zero
    mat4 modelBuffer[MAX_INSTANCES];
    memset(&modelBuffer[0], 0, MAX_INSTANCES * 16 * sizeof(float));

    //Create vbos, send it data, configure vao and set the attrib divisors
    //vbo1 (vertice data)
    unsigned int* vbo1 = createVertexBuffer(vertices, sizeof(vertices));
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);  

    //vbo2 (model matrix buffer - maximum size for vertex attributes is a vec4 
    //so we need to send 4 consecutive vec4's to simulate a mat4) 
    unsigned int* vbo2 = createDynamicVertexBuffer(&modelBuffer[0], MAX_INSTANCES * 16 * sizeof(float));

    defineVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);    
    defineVertexAttributes(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));    
    defineVertexAttributes(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));    
    defineVertexAttributes(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));  

    setAttributeDivisor(1, 1);
    setAttributeDivisor(2, 1);
    setAttributeDivisor(3, 1);
    setAttributeDivisor(4, 1);

    unbindVertexArray(vao);
    unbindVertexBuffer(vbo1);
    unbindVertexBuffer(vbo2);

    //Delete vertice data vbo -> not needed anymore and it will not get passed into the struct
    deleteVertexBuffer(vbo1);

    //Create struct and fill it with data
    ObjInstance instance;
    instance.instanceID = instanceID;
    instance.instanceAmount = 0;
    instance.vao = vao;
    instance.vboM = vbo2;
    memcpy(&instance.modelBuffer, &modelBuffer, MAX_INSTANCES * 16 * sizeof(float));
    instance.texture = texture;
    instance.shader = resourceManagerGetShader("instancedShader");
    instance.color[0] = color[0];
    instance.color[1] = color[1];
    instance.color[2] = color[2];

    //Copy sprite onto the heap and return it
    void* mem = malloc(sizeof(ObjInstance));
    memcpy(mem, &instance, sizeof(ObjInstance));

    instanceID++;        

    return (ObjInstance*)mem;    
}

void objectInstancerAddInstance(ObjInstance* instance, float* position)
{
    if(instance->instanceAmount < MAX_INSTANCES)
    {
        //Create model matrix with new transformations
        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model, (vec3){position[0], position[1], 1.0f});
        glm_scale(model, (vec3){100.0f, 100.0f, 1.0f});

        //Copy model matrix into model buffer
        memcpy(&instance->modelBuffer[instance->instanceAmount], &model, sizeof(mat4));
        
        //Send model buffer to the gpu
        bindVertexBuffer(instance->vboM);
        updateDynamicVertexBuffer(&instance->modelBuffer[0], MAX_INSTANCES * 16 * sizeof(float));
        unbindVertexBuffer();

        instance->instanceAmount++;
    }
}

void objectInstancerDeleteInstance(ObjInstance* instance)
{
    deleteVertexBuffer(instance->vboM);
    deleteVertexArray(instance->vao);

    free(instance);
}