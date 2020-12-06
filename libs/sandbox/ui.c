#include "ui.h"

void uiInit()
{
    //Allocate resources
    blockTexture = createTexture("res/textures/Block.jpg");
    blockSolidTexture = createTexture("res/textures/Block_solid.jpg");
    pickaxeTexture = createTexture("res/textures/Pickaxe.png");
    bgTexture = createTexture("res/textures/Background.jpg");
    sbTexture = createTexture("res/textures/Sidebar.png");

    standardShader = createShader("res/shader/standard_vs.glsl", "res/shader/standard_fs.glsl");    

    vertexData = createVertexData(); 

    //Create sprites
    sprites[0] = createSprite(vertexData, bgTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){WIDTH, HEIGHT}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);       

    sprites[1] = createSprite(vertexData, sbTexture, standardShader, (vec2){1300.0f, 0.0f}, 
                             (vec2){300.0f, HEIGHT}, 0.0f, (vec3){0.45f, 0.45f, 0.45f}, false); 

    sprites[2] = createSprite(vertexData, pickaxeTexture, standardShader, (vec2){1333.3f, 33.3f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.4f, 0.4f, 0.4f}, true); 

    sprites[3] = createSprite(vertexData, blockTexture, standardShader, (vec2){1333.3f, 166.6f},
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.7f, 0.6f, 0.4f}, true); 

    sprites[4] = createSprite(vertexData, blockSolidTexture, standardShader, (vec2){1466.6f, 166.6f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.3f, 0.1f, 0.1f}, true);                           
}

void uiRender()
{   
    for(int i = 0; i < UI_ELEMENTS; i++)
    {
        if(sprites[i]->isClickable)
        {
            int result;
            result = uiGetButtonState(sprites[i]);

            if(result == 0) //Standard button state
                renderSprite(sprites[i], 1.0f, (vec3){1.0f, 1.0f, 1.0f});
            else if(result == 1) //Hovered button state
                renderSprite(sprites[i], 1.1f, (vec3){0.98f, 0.7f, 0.0f});
            else if(result == 2) //Clicked button state
                renderSprite(sprites[i], 1.0f, (vec3){0.25f, 0.98f, 0.0f});
        }
        else
        {
            renderSprite(sprites[i], 1.0f, (vec3){1.0f, 1.0f, 1.0f});
        }           
    } 
}

void uiCleanUp()
{
    //Delete resources
    deleteTexture(blockTexture);
    deleteTexture(blockSolidTexture);
    deleteTexture(pickaxeTexture);
    deleteTexture(bgTexture);
    deleteTexture(sbTexture);

    deleteShader(standardShader);
    deleteVertexData(vertexData);

    //Delete sprites
    for(int i = 0; i < UI_ELEMENTS; i++)
        deleteSprite(sprites[i]);
}

static bool uiButtonHover(int* x, int* y, Sprite* sprite)
{
    //Called every frame to check if mouse cursor is inside one of the clickable buttons

    int mouse_x = *x;
    int mouse_y = *y;
    int sprite_x1 = (int)(sprite->position[0]);
    int sprite_x2 = (int)(sprite->position[0] + sprite->size[0]);
    int sprite_y1 = (int)(sprite->position[1]);
    int sprite_y2 = (int)(sprite->position[1] + sprite->size[1]);

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