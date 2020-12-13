#include "ui.h"

bool placementMode = false;

void uiInit()
{
    //Get resources
    unsigned int* blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int* solidBlockTexture = resourceManagerGetTexture("solidBlockTexture");
    unsigned int* pickaxeTexture = resourceManagerGetTexture("pickaxeTexture");
    unsigned int* bgTexture = resourceManagerGetTexture("backgroundTexture");
    unsigned int* sbTexture = resourceManagerGetTexture("sidebarTexture");
    unsigned int* highlightTexture = resourceManagerGetTexture("highlightTexture");
    unsigned int* standardShader = resourceManagerGetShader("standardShader");
    unsigned int* spriteData = resourceManagerGetSpriteData();

    //Create sprites
    sprites[0] = createSprite(spriteData, bgTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){WIDTH, HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);       

    sprites[1] = createSprite(spriteData, sbTexture, standardShader, (vec2){1300.0f, 0.0f}, 
                             (vec2){300.0f, HEIGHT}, 0.0f, (vec3){0.45f, 0.45f, 0.45f}, false); 

    sprites[2] = createSprite(spriteData, pickaxeTexture, standardShader, (vec2){1333.3f, 33.3f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.6f, 0.6f, 0.6f}, true); 

    sprites[3] = createSprite(spriteData, blockTexture, standardShader, (vec2){1333.3f, 166.6f},
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.7f, 0.6f, 0.4f}, true); 

    sprites[4] = createSprite(spriteData, solidBlockTexture, standardShader, (vec2){1466.6f, 166.6f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, true);           

    highlighter = createSprite(spriteData, highlightTexture, standardShader, (vec2){500.0f, 500.0f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.98f, 0.7f, 0.0f}, false);                                          
}

void uiRenderElements()
{   
    for(int i = 0; i < UI_ELEMENTS; i++)
    {
        if(sprites[i]->isClickable)
        {
            int result;
            result = uiGetButtonState(sprites[i]);

            if(result == 0) //Standard button state
            {
                glm_vec3_copy(sprites[i]->baseColor, sprites[i]->currentColor);
                renderSimpleSprite(sprites[i]);
            }                
            else if(result == 1) //Hovered button state
            {
                glm_vec3_copy((vec3){0.0f, 0.78f, 0.95f}, sprites[i]->currentColor);
                renderSimpleSprite(sprites[i]);
            }                
            else if(result == 2) //Clicked button state
            {
                glm_vec3_copy((vec3){0.98f, 0.7f, 0.0f}, sprites[i]->currentColor);
                renderSimpleSprite(sprites[i]);
            }                
        }
        else
        {
            glm_vec3_copy(sprites[i]->baseColor, sprites[i]->currentColor);
            renderSimpleSprite(sprites[i]);
        }     
    } 
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
        renderSimpleSprite(highlighter);
        placementMode = true;
    }
}

void uiCleanUp()
{
    //Delete sprites
    for(int i = 0; i < UI_ELEMENTS; i++)
        deleteSprite(sprites[i]);

    deleteSprite(highlighter); 
}

static bool uiButtonHover(int* x, int* y, Sprite* sprite)
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

static int uiGetButtonState(Sprite* sprite)
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