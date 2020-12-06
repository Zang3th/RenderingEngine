#include "ui.h"

void uiInit()
{
    //Allocate resources
    blockTexture = createTexture("res/textures/Block.jpg");
    blockSolidTexture = createTexture("res/textures/Block_solid.jpg");
    pickaxeTexture = createTexture("res/textures/Pickaxe.png");
    bgTexture = createTexture("res/textures/Background.jpg");
    sbTexture = createTexture("res/textures/Sidebar.png");

    shader = createShader("res/shader/basic_vs.glsl", "res/shader/basic_fs.glsl");    
    vertexData = createVertexData(); 

    //Create sprites
    sprites[0] = createSprite(vertexData, bgTexture, shader,
                             (vec2){0.0f, 0.0f}, (vec2){WIDTH, HEIGHT},
                              0.0f, (vec3){1.0f, 1.0f, 1.0f});       

    sprites[1] = createSprite(vertexData, sbTexture, shader,
                             (vec2){1300.0f, 0.0f}, (vec2){300.0f, HEIGHT},
                              0.0f, (vec3){0.45f, 0.45f, 0.45f}); 

    sprites[2] = createSprite(vertexData, pickaxeTexture, shader,
                             (vec2){1333.3f, 33.3f}, (vec2){100.0f, 100.0f},
                              0.0f, (vec3){0.4f, 0.4f, 0.4f}); 

    sprites[3] = createSprite(vertexData, blockTexture, shader,
                             (vec2){1333.3f, 166.6f}, (vec2){100.0f, 100.0f},
                              0.0f, (vec3){0.7f, 0.6f, 0.4f}); 

    sprites[4] = createSprite(vertexData, blockSolidTexture, shader,
                             (vec2){1466.6f, 166.6f}, (vec2){100.0f, 100.0f},
                              0.0f, (vec3){0.3f, 0.1f, 0.1f});                
}

void uiRender()
{
    for(int i = 0; i < UI_ELEMENTS; i++)
        renderSprite(sprites[i]);
}

void uiCleanUp()
{
    //Delete resources
    deleteTexture(blockTexture);
    deleteTexture(blockSolidTexture);
    deleteTexture(pickaxeTexture);
    deleteTexture(bgTexture);
    deleteTexture(sbTexture);

    deleteShader(shader);
    deleteVertexData(vertexData);

    //Delete sprites
    for(int i = 0; i < UI_ELEMENTS; i++)
        deleteSprite(sprites[i]);
}