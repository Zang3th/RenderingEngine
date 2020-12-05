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
    spriteData = initSpriteData();  
}

void uiRender()
{
    renderSprite(spriteData, bgTexture, shader, 
                (vec2){0.0f, 0.0f}, (vec2){WIDTH, HEIGHT},
                 0.0f, (vec3){1.0f, 1.0f, 1.0f});

    renderSprite(spriteData, sbTexture, shader, 
                (vec2){1300.0f, 0.0f}, (vec2){300.0f, HEIGHT},
                 0.0f, (vec3){0.45f, 0.45f, 0.45f});   

    renderSprite(spriteData, pickaxeTexture, shader, 
                (vec2){1333.3f, 33.3f}, (vec2){100.0f, 100.0f},
                 0.0f, (vec3){0.4f, 0.4f, 0.4f});        

    renderSprite(spriteData, blockTexture, shader, 
                (vec2){1333.3f, 166.6f}, (vec2){100.0f, 100.0f},
                 0.0f, (vec3){0.7f, 0.6f, 0.4f});  

    renderSprite(spriteData, blockSolidTexture, shader, 
                (vec2){1466.6f, 166.6f}, (vec2){100.0f, 100.0f},
                 0.0f, (vec3){0.3f, 0.1f, 0.1f});      
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
    deleteSpriteData(spriteData);
}