#include "ui.h"

static bool uiButtonHover(int* x, int* y, sprite_t* sprite)
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

static int uiGetButtonState(sprite_t* sprite)
{
    //return 0 for standard rendering
    //return 1 for hover rendering
    //return 2 for click rendering

    int x, y;
    windowGetMousePos(&x, &y);
    bool isHovered = uiButtonHover(&x, &y, sprite);
    bool gotAlreadyClicked = sprite->gotClicked;
    
    if(activeElement != NULL)
    {
        if(gotAlreadyClicked)
        {
            if(rightMousePressed)
            {
                sprite->gotClicked = false;
                activeElement = NULL;
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
            activeElement = sprite;
            return 2;
        }
        else if(isHovered)
            return 1;        

        return 0;
    }
}

static void uiChangeButtonState(sprite_t* sprite, int result, int count)
{    
    if(result == 1) //Hovered button state
    {
        glm_vec3_copy((vec3){0.7f, 0.7f, 0.7f}, sprite->currentColor);
    }                
    else if(result == 2) //Clicked button state
    {  
        if(count == trashCanID)
        {
            glm_vec3_copy(sprite->baseColor, sprite->currentColor);
            activeElement = NULL;
            sprite->gotClicked = false;
        }
        else
        {
            activeElement = sprite;
        }                             
    }
}

void uiInit()
{
    for(int i = 0; i < UI_ELEMENTS_MAX; i++)
        ui_Elements[i] = NULL;
}

void uiAddElement(sprite_t* sprite)
{
    ui_Elements[numberOfElements] = sprite;
    numberOfElements++; 
}

void uiAddHighlighter(sprite_t* sprite)
{
    highlighter = sprite;
}

void uiAddTrashcan(sprite_t* sprite)
{
    trashCanID = numberOfElements;
    uiAddElement(sprite);
}

void uiRender()
{
    for(int i = 0; i < numberOfElements; i++)
    {
        if(ui_Elements[i]->isClickable)
        {
            //Reset color
            glm_vec3_copy(ui_Elements[i]->baseColor, ui_Elements[i]->currentColor); 

            //Check for action
            int result;
            result = uiGetButtonState(ui_Elements[i]);     

            //Branch if button got hovered or clicked
            if(result != 0) 
            {
                uiChangeButtonState(ui_Elements[i], result, i);
            }          

            renderSprite(ui_Elements[i]);
        }
        else
            renderSprite(ui_Elements[i]);
    }

    if(activeElement != NULL)
    {
        translateSprite(highlighter, (vec2){activeElement->basePosition[0], activeElement->basePosition[1]});
        renderSprite(highlighter);
    }
}

void uiCleanUp()
{
    for(int i = 0; i < numberOfElements; i++)
        deleteSprite(ui_Elements[i]); 

    deleteSprite(highlighter);      
}

sprite_t* uiGetPressedButton()
{
    return activeElement;
}