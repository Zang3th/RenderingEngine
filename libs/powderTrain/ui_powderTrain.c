#include "ui_powderTrain.h"

void uiInit()
{
    //Get resources
    unsigned int bgTexture = resourceManagerGetTexture("backgroundTexture");
    unsigned int sbTexture = resourceManagerGetTexture("sidebarTexture");
    unsigned int blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int trashcanTexture = resourceManagerGetTexture("trashcanTexture");
    unsigned int highlightTexture = resourceManagerGetTexture("highlightTexture");
    unsigned int standardShader = resourceManagerGetShader("standardShader");
    unsigned int spriteData = resourceManagerGetSpriteData();

    //Create sprites
    sprites[0] = createSprite(spriteData, bgTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){WIDTH, HEIGHT}, 0.0f, (vec3){0.7f, 0.7f, 0.7f}, false);

    sprites[1] = createSprite(spriteData, sbTexture, standardShader, (vec2){1500.0f, 0.0f}, 
                             (vec2){100.0f, HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);

    sprites[2] = createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 25.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.778f, 0.664f, 0.241f}, true); 

    sprites[3] = createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 125.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.060f, 0.464f, 0.9f}, true); 

    sprites[4] = createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 225.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.560f, 0.560f, 0.560f}, true);  

    sprites[5] = createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 325.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.858f, 0.0f, 0.019f}, true); 

    sprites[6] = createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 425.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.113f, 0.858f, 0.0f}, true); 

    sprites[7] = createSprite(spriteData, blockTexture, standardShader, (vec2){1512.5f, 525.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.478f, 0.274f, 0.0f}, true);  

    sprites[8] = createSprite(spriteData, trashcanTexture, standardShader, (vec2){1512.5f, 800.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true);                                                  

    highlighter = createSprite(spriteData, highlightTexture, standardShader, (vec2){500.0f, 500.0f}, 
                             (vec2){75.0f, 75.0f}, 0.0f, (vec3){0.98f, 0.7f, 0.0f}, false);                       
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
    textBatchRendererAddText("Sand", 1525.5f, 825.0f, 0.55f);
    textBatchRendererAddText("Water", 1518.5f, 725.0f, 0.55f);
    textBatchRendererAddText("Stone", 1519.5f, 625.0f, 0.55f);
    textBatchRendererAddText("Fire", 1530.5f, 525.0f, 0.55f);
    textBatchRendererAddText("Acid", 1530.5f, 425.0f, 0.55f);
    textBatchRendererAddText("Wood", 1521.5f, 325.0f, 0.55f);
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
        glm_vec3_copy((vec3){0.7f, 0.7f, 0.7f}, sprite->currentColor);
    }                
    else if(result == 2) //Clicked button state
    {
        if(count == 8) //Delete button pressed
        {
            glm_vec3_copy(sprite->baseColor, sprite->currentColor);
            uiDeleteButtonPressed();
        }
        else if(count == 2 || count == 3 || count == 4 || count == 5 || count == 6 || count == 7) //Activate corresponding button
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
    elementActive = false;
    sprites[8]->gotClicked = false;
}