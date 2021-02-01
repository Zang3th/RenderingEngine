#include "ui.h"

bool placementMode = false;

void uiInit()
{
    //Get resources
    unsigned int* blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int* solidBlockTexture = resourceManagerGetTexture("solidBlockTexture");
    unsigned int* trashcanTexture = resourceManagerGetTexture("trashcanTexture");
    unsigned int* bgTexture = resourceManagerGetTexture("backgroundTexture");
    unsigned int* sbTexture = resourceManagerGetTexture("sidebarTexture");
    unsigned int* bucketTexture = resourceManagerGetTexture("bucketTexture");
    unsigned int* stickmanTexture = resourceManagerGetTexture("stickmanTexture");
    unsigned int* highlightTexture = resourceManagerGetTexture("highlightTexture");
    unsigned int* standardShader = resourceManagerGetShader("standardShader");
    unsigned int* spriteData = resourceManagerGetSpriteData();

    //Create sprites
    sprites[0] = createSprite(spriteData, bgTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){WIDTH, HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);       

    sprites[1] = createSprite(spriteData, sbTexture, standardShader, (vec2){1300.0f, 0.0f}, 
                             (vec2){300.0f, HEIGHT}, 0.0f, (vec3){0.7f, 0.7f, 0.7f}, false); 

    sprites[2] = createSprite(spriteData, trashcanTexture, standardShader, (vec2){1466.6f, HEIGHT - 133.3f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true); 

    sprites[3] = createSprite(spriteData, blockTexture, standardShader, (vec2){1333.3f, 66.6f},
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true); 

    sprites[4] = createSprite(spriteData, solidBlockTexture, standardShader, (vec2){1466.6f, 66.6f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.7f, 0.7f, 0.7f}, true);    

    sprites[5] = createSprite(spriteData, bucketTexture, standardShader, (vec2){1323.3f, 233.3f},
                             (vec2){120.0f, 120.0f}, 0.0f, (vec3){0.85f, 0.85f, 0.85f}, true); 

    sprites[6] = createSprite(spriteData, stickmanTexture, standardShader, (vec2){1476.6f, 233.3f}, 
                             (vec2){80.0f, 120.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true);         

    highlighter = createSprite(spriteData, highlightTexture, standardShader, (vec2){500.0f, 500.0f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.98f, 0.7f, 0.0f}, false);                                                                
}

void uiRenderElements()
{   
    //Deactivate highlight box for certain elements
    activeElement = NULL;

    for(int i = 0; i < UI_ELEMENTS; i++)
    {
        if(sprites[i]->isClickable)
        {
            //Reset color
            glm_vec3_copy(sprites[i]->baseColor, sprites[i]->currentColor); 

            //Check for action
            int result;
            result = uiGetButtonState(sprites[i]);     

            //Branch if button got hovered or clicked
            if(result != 0) 
            {
                uiChangeButtonState(sprites[i], result, i);
            }          

            renderSprite(sprites[i]);
        }
        else
            renderSprite(sprites[i]);
    } 

    if(activeElement != NULL)
    {
        translateSprite(highlighter, (vec2){activeElement->basePosition[0], activeElement->basePosition[1]});
        renderSprite(highlighter);
    }
}

void uiAddText()
{   
    textBatchRendererAddText("Box", 1357.5f, 850.0f, 0.7f);
    textBatchRendererAddText("Block", 1485.0f, 850.0f, 0.7f);
    textBatchRendererAddText("Water", 1342.5f, 675.0f, 0.7f);
    textBatchRendererAddText("Player", 1480.0f, 675.0f, 0.7f);
    textBatchRendererAddText("Erase all", 1460.0f, 140.0f, 0.7f);
}

void uiRenderHighlighter()
{
    //Get mouse position
    int mouse_x, mouse_y;
    windowGetMousePos(&mouse_x, &mouse_y);
    placementMode = false;

    //Check if mouse is outside of the sidebar and an element is active/chosen
    if(!uiButtonHover(&mouse_x, &mouse_y, sprites[1]) && elementActive)
    {  
        //Correct mouse position if its outside of the main window bounds
        int new_mouse_x = mouse_x;
        int new_mouse_y = mouse_y;

        if(mouse_x < 50)
            new_mouse_x = 50;
        else if(mouse_x > 1250)
            new_mouse_x = 1250;

        if(mouse_y < 50)
            new_mouse_y = 50;
        else if(mouse_y > 850)
            new_mouse_y = 850;

        windowSetMousePos(new_mouse_x, new_mouse_y);

        //Translate highlighter to mouse position and render it
        translateSprite(highlighter, (vec2){(float)new_mouse_x - 50.0f, (float)new_mouse_y - 50.0f});
        renderSprite(highlighter);
        placementMode = true;
    }
}

int uiGetBlockmode()
{
    //Check for block placement mode
    if(sprites[3]->gotClicked == true)
        return 1;

    //Check for solid block placement mode    
    else if(sprites[4]->gotClicked == true)
        return 2;

    //Else nothing should be placed
    return -1;            
}

void uiCleanUp()
{
    //Delete sprites
    for(int i = 0; i < UI_ELEMENTS; i++)
        deleteSprite(sprites[i]);

    deleteSprite(highlighter); 
}

bool uiButtonHover(int* x, int* y, sprite_t* sprite)
{
    //Called every frame to check if mouse cursor is inside one of the clickable buttons

    int mouse_x = *x;
    int mouse_y = *y;
    int sprite_x1 = (int)(sprite->basePosition[0]);
    int sprite_x2 = (int)(sprite->basePosition[0] + sprite->baseSize[0]);
    int sprite_y1 = (int)(sprite->basePosition[1]);
    int sprite_y2 = (int)(sprite->basePosition[1] + sprite->baseSize[1]);

    if(mouse_x >= sprite_x1 && mouse_x <= sprite_x2 && mouse_y >= sprite_y1 && mouse_y <= sprite_y2)
        return true;
    
    return false;        
}

int uiGetButtonState(sprite_t* sprite)
{
    //return 0 for standard rendering
    //return 1 for hover rendering
    //return 2 for click rendering

    int x, y;
    windowGetMousePos(&x, &y);
    bool isHovered = uiButtonHover(&x, &y, sprite);
    bool gotAlreadyClicked = sprite->gotClicked;
    
    if(elementActive)
    {
        if(gotAlreadyClicked)
        {
            if(rightMousePressed)
            {
                sprite->gotClicked = false;
                elementActive = false;
                return 0;
            }

            return 2;
        }

        return 0;
    }
    else
    {
        if(isHovered && leftMousePressed)
        {
            sprite->gotClicked = true;
            elementActive = true;
            return 2;
        }
        else if(isHovered)
            return 1;        

        return 0;
    }
}

void uiChangeButtonState(sprite_t* sprite, int result, int count)
{    
    if(result == 1) //Hovered button state
    {
        glm_vec3_copy((vec3){0.0f, 0.78f, 0.95f}, sprite->currentColor);
    }                
    else if(result == 2) //Clicked button state
    {
        if(count == 2) //Delete button pressed
        {
            glm_vec3_copy(sprite->baseColor, sprite->currentColor);
            uiDeleteButtonPressed();
        }
        else if(count == 3 || count == 4) //Elements with highlight box pressed
        {
            activeElement = sprite;
        } 
        else //Other elements pressed
        {                
            glm_vec3_copy((vec3){0.98f, 0.7f, 0.0f}, sprite->currentColor);
        }                                              
    }
}

void uiDeleteButtonPressed()
{
    placementMode = false;
    elementActive = false;
    sprites[2]->gotClicked = false;
    objectManagerDeleteAllObjects();
}