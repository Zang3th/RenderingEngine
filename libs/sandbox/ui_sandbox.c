#include "ui_sandbox.h"

bool placementMode = false;

static void uiTrashcanCallback_sandbox()
{
    objectManagerDeleteAllObjects();
}

void uiInit_sandbox()
{
    //Init UI
    uiInit((vec3){0.0f, 0.78f, 0.95f});
    uiDefineTrashcanCallback(uiTrashcanCallback_sandbox);

    //Get resources
    unsigned int blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int solidBlockTexture = resourceManagerGetTexture("solidBlockTexture");
    unsigned int trashcanTexture = resourceManagerGetTexture("trashcanTexture");
    unsigned int bgTexture = resourceManagerGetTexture("backgroundTexture");
    unsigned int sbTexture = resourceManagerGetTexture("sidebarTexture");
    unsigned int bucketTexture = resourceManagerGetTexture("bucketTexture");
    unsigned int stickmanTexture = resourceManagerGetTexture("stickmanTexture");
    unsigned int highlightTexture = resourceManagerGetTexture("highlightTexture");
    unsigned int standardShader = resourceManagerGetShader("standardShader");
    unsigned int spriteData = resourceManagerGetSpriteData();

    //Create sprites and add them to UI
    bgID = uiAddElement(createSprite(spriteData, bgTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){WIDTH, HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false));       

    sbID = uiAddElement(createSprite(spriteData, sbTexture, standardShader, (vec2){1300.0f, 0.0f}, 
                             (vec2){300.0f, HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false)); 

    blockID = uiAddElement(createSprite(spriteData, blockTexture, standardShader, (vec2){1333.3f, 66.6f},
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true)); 

    solidBlockID = uiAddElement(createSprite(spriteData, solidBlockTexture, standardShader, (vec2){1466.6f, 66.6f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.7f, 0.7f, 0.7f}, true));    

    bucketID = uiAddElement(createSprite(spriteData, bucketTexture, standardShader, (vec2){1323.3f, 233.3f},
                             (vec2){120.0f, 120.0f}, 0.0f, (vec3){0.85f, 0.85f, 0.85f}, true)); 

    stickmanID = uiAddElement(createSprite(spriteData, stickmanTexture, standardShader, (vec2){1476.6f, 233.3f}, 
                             (vec2){80.0f, 120.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true));         

    uiAddTrashcan(createSprite(spriteData, trashcanTexture, standardShader, (vec2){1466.6f, HEIGHT - 133.3f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true));

    uiAddHighlighter(createSprite(spriteData, highlightTexture, standardShader, (vec2){500.0f, 500.0f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.98f, 0.7f, 0.0f}, false)); 
}

void uiAddText_sandbox()
{
    textBatchRendererAddText("Box", 1357.5f, 850.0f, 0.7f);
    textBatchRendererAddText("Block", 1485.0f, 850.0f, 0.7f);
    textBatchRendererAddText("Water", 1342.5f, 675.0f, 0.7f);
    textBatchRendererAddText("Player", 1480.0f, 675.0f, 0.7f);
    textBatchRendererAddText("Erase all", 1460.0f, 140.0f, 0.7f);
}

int uiGetBlockmode_sandbox()
{
    //Get pressed button
    sprite_t* pressedButton = uiGetPressedButtonSprite();
   
    //Branch if a button is pressed
    if(pressedButton != NULL)
    {   
        //Check for block placement mode
        if(uiIsButtonPressed(blockID))
            return 1;

        //Check for solid block placement mode    
        else if(uiIsButtonPressed(solidBlockID))
            return 2;
    }

    //Else nothing should be placed
    return -1;
}

void uiRender_sandbox()
{
    uiRender();
}

void uiRenderHighlighter_sandbox()
{
    //Get mouse position
    double mouse_x, mouse_y;
    window2DGetMousePos(&mouse_x, &mouse_y);
    placementMode = false;

    //Check if mouse is outside of the sidebar and an element is active/chosen
    bool isInsideBar = uiIsButtonHovered(&mouse_x, &mouse_y, sbID);
    sprite_t* pressedButton = uiGetPressedButtonSprite();

    if((isInsideBar == false) && (pressedButton != NULL))
    {  
        //Correct mouse position if its outside of the main window bounds
        double new_mouse_x = mouse_x;
        double new_mouse_y = mouse_y;

        if(mouse_x < 50)
            new_mouse_x = 50;
        else if(mouse_x > 1250)
            new_mouse_x = 1250;

        if(mouse_y < 50)
            new_mouse_y = 50;
        else if(mouse_y > 850)
            new_mouse_y = 850;

        //Translate highlighter to mouse position and render it
        translateSprite(highlighter, (vec2){(float)new_mouse_x - 50.0f, (float)new_mouse_y - 50.0f});
        renderSprite(highlighter);
        placementMode = true;
    }
}

void uiCleanUp_sandbox()
{
    uiCleanUp();
}