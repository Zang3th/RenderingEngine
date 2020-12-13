#include "objectManager.h"

void objectManagerInit()
{    
    //Get resources
    unsigned int* blockTexture = resourceManagerGetTexture("blockTexture");
    unsigned int* standardShader = resourceManagerGetShader("standardShader");
    unsigned int* spriteData = resourceManagerGetSpriteData();

    //Create sprite
    objSprite = createSprite(spriteData, blockTexture, standardShader, (vec2){0.0f, 0.0f}, 
                             (vec2){100.0f, 100.0f}, 0.0f, (vec3){0.7f, 0.6f, 0.4f}, false); 
}

void objectManagerRenderObjects()
{
    addObjectToRenderqueue();

    for(int i = 0; i < objectCount; i++)
    {
        float x = objectPositions[i][0];
        float y = objectPositions[i][1];
        translateSprite(objSprite, (vec2){x - 50.0f, y - 50.0f});
        renderSimpleSprite(objSprite);
    }
}

void objectManagerCleanUp()
{
    deleteSprite(objSprite);
}

static void addObjectToRenderqueue()
{
    if(objectCount < OBJECT_COUNT_MAX)
    {
        //Check if app is in object placement mode and if left mouse button is pressed
        if(placementMode && leftMousePressed)
        {
            //Add current mouse position to position array for the renderqueue
            int x, y;
            windowGetMousePos(&x, &y);
            if(x != last_x || y != last_y)
            {
                vec2 v = {(float)x, (float)y};
                memcpy(&objectPositions[objectCount], &v, sizeof(vec2));
                objectCount++;
                last_x = x;
                last_y = y;
            }            
        }
    }    
}