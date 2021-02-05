#include "objectManager.h"

void objectManagerInit()
{    
    //Get resources
    unsigned int blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int solidBlockTexture = resourceManagerGetTexture("solidBlockTexture");

    //Create base instance
    blockInstance = objectInstancerCreateInstance(blockTexture, (vec3){1.0f, 1.0f, 1.0f}, 100.0f, 1.0f);
    solidBlockInstance = objectInstancerCreateInstance(solidBlockTexture, (vec3){0.7f, 0.7f, 0.7f}, 100.0f, 50.0f);
}

void objectManagerRenderObjects()
{
    renderInstancedSprite(blockInstance);
    renderInstancedSprite(solidBlockInstance);
}

void objectManagerDeleteAllObjects()
{
    blockInstance->instanceAmount = 0;
    solidBlockInstance->instanceAmount = 0;
    objectInstancerDeletePhysicsInstance(blockInstance);
    objectInstancerDeletePhysicsInstance(solidBlockInstance);
}

void objectManagerCheckForPlacement()
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
                last_x = x;
                last_y = y; 

                vec2 v = {(float)x - 50.0f, (float)y - 50.0f};
                objectInstancerAddInstance(blockInstance, (float*) v);
            }
        }
        else if(mode == 2) //solidBlockMode
        {
            if(x != last_x || y != last_y)
            {
                last_x = x;
                last_y = y; 

                vec2 v = {(float)x - 50.0f, (float)y - 50.0f};
                objectInstancerAddInstance(solidBlockInstance, (float*) v);
            }
        }            
    }        
}

void objectManagerCleanUp()
{
    objectInstancerDeleteInstance(blockInstance);
    objectInstancerDeleteInstance(solidBlockInstance);
}