#include "ui_powderTrain.h"

static void uiTrashcanCallback_powderTrain()
{
    //Do stuff
}

void uiInit_powderTrain()
{
    //Init UI
    uiInit((vec3){0.8f, 0.8f, 0.8f});
    uiDefineTrashcanCallback(uiTrashcanCallback_powderTrain);

    //Get resources
    unsigned int bgTexture = resourceManagerGetTexture("backgroundTexture");
    unsigned int sbTexture = resourceManagerGetTexture("sidebarTexture");
    unsigned int blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int trashcanTexture = resourceManagerGetTexture("trashcanTexture");
    unsigned int highlightTexture = resourceManagerGetTexture("highlightTexture");
    unsigned int standardShader = resourceManagerGetShader("standardShader");
    unsigned int spriteData = resourceManagerGetSpriteData();

    //Create sprites and add them to UI
    bgID = uiAddElement(createSprite(spriteData, bgTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){WIDTH, HEIGHT}, 0.0f, (vec3){0.7f, 0.7f, 0.7f}, false));

    sbID = uiAddElement(createSprite(spriteData, sbTexture, standardShader, (vec2){1500.0f, 0.0f}, 
                             (vec2){100.0f, HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false));

    sandID = uiAddElement(createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 25.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.778f, 0.664f, 0.241f}, true)); 

    waterID = uiAddElement(createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 125.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.060f, 0.464f, 0.9f}, true)); 

    stoneID = uiAddElement(createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 225.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.560f, 0.560f, 0.560f}, true));  

    fireID = uiAddElement(createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 325.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.858f, 0.0f, 0.019f}, true)); 

    acidID = uiAddElement(createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 425.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.113f, 0.858f, 0.0f}, true)); 

    woodID = uiAddElement(createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 525.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.478f, 0.274f, 0.0f}, true));  

    uiAddTrashcan(createSprite(spriteData, trashcanTexture, standardShader, (vec2){1512.5f, 800.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true));                                                  

    uiAddHighlighter(createSprite(spriteData, highlightTexture, standardShader, (vec2){500.0f, 500.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.98f, 0.7f, 0.0f}, false));
}

void uiRender_powderTrain()
{
    uiRender();
}

void uiAddText_powderTrain()
{
    textBatchRendererAddText("Sand", 1525.5f, 825.0f, 0.55f);
    textBatchRendererAddText("Water", 1518.5f, 725.0f, 0.55f);
    textBatchRendererAddText("Stone", 1519.5f, 625.0f, 0.55f);
    textBatchRendererAddText("Fire", 1530.5f, 525.0f, 0.55f);
    textBatchRendererAddText("Acid", 1530.5f, 425.0f, 0.55f);
    textBatchRendererAddText("Wood", 1521.5f, 325.0f, 0.55f);
}

void uiCleanUp_powderTrain()
{
    uiCleanUp();
}