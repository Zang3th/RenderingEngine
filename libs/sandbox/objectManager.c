#include "objectManager.h"

void objectManagerInit()
{    
    //Get resources
    unsigned int* blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int* solidBlockTexture = resourceManagerGetTexture("solidBlockTexture");
    unsigned int* standardShader = resourceManagerGetShader("standardShader");
    unsigned int* spriteData = resourceManagerGetSpriteData();

    //Create sprite
    blockObject = createSprite(spriteData, blockTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.7f, 0.6f, 0.4f}, false); 

    solidBlockObject = createSprite(spriteData, solidBlockTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);                          
}

void objectManagerRenderObjects()
{
    for(int i = 0; i < objectCount; i++)
    {        
        float x = objects[i].position[0];
        float y = objects[i].position[1];

        if(objects[i].type == 1)
        {
            translateSprite(blockObject, (vec2){x, y});
            renderSimpleSprite(blockObject);
        }
        else if(objects[i].type == 2)
        {
            translateSprite(solidBlockObject, (vec2){x, y});
            renderSimpleSprite(solidBlockObject);
        }
    }
}

void objectManagerDeleteAllObjects()
{
    objectCount = 0;
}

void objectManagerCheckForPlacement()
{
    if(objectCount < OBJECT_COUNT_MAX)
    {
        //Check if app is in object placement mode and if left mouse button is pressed
        if(placementMode && leftMousePressed)
        {
            //Add current mouse position to position array for the renderqueue
            int x, y;
            windowGetMousePos(&x, &y);
             
            //Get current active mode from the UI 
            int mode = uiGetBlockmode();

            if(mode == 1) //Blockmode
            {
                if(x != last_x || y != last_y)
                {
                    vec2 v = {(float)x - 50.0f, (float)y - 50.0f};
                    memcpy(&objects[objectCount].position, &v, sizeof(vec2));
                    memcpy(&objects[objectCount].type, &mode, sizeof(int));
                    objectCount++;
                    last_x = x;
                    last_y = y;
                }
            }
            else if(mode == 2) //solidBlockMode
            {
                if(x != last_x || y != last_y)
                {
                    vec2 v = {(float)x - 50.0f, (float)y - 50.0f};
                    memcpy(&objects[objectCount].position, &v, sizeof(vec2));
                    memcpy(&objects[objectCount].type, &mode, sizeof(int));
                    objectCount++;
                    last_x = x;
                    last_y = y;
                }
            }            
        }
    }    
}

void objectManagerCleanUp()
{
    deleteSprite(blockObject);
    deleteSprite(solidBlockObject);
}