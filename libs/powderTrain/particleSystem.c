#include "particleSystem.h"

static void particleSystemSpawnElement(unsigned int index)
{
    //Add particle into particle array corresponding to mouse position
    //Set cell color depending on the spawned element

    printf("SPAWN! %d\n", index);
}

void particleSystemInit()
{
    //Init pixel renderer
    pixelRendererInit("res/textures/powderTrain/Background_1500x900.jpg");

    pixelRendererSet(1, 1, (vec3){1.0f, 0.0f, 0.0f});
    pixelRendererSet(1, 900, (vec3){1.0f, 0.0f, 0.0f});
    pixelRendererSet(1500, 1, (vec3){1.0f, 0.0f, 0.0f});
    pixelRendererSet(1500, 900, (vec3){1.0f, 0.0f, 0.0f});  
}

void particleSystemCheckSpawn()
{
    //Check for button press
    int pressedButton = uiGetPressedButton_powderTrain();

    //If a button is pressed and left mouse is hold 
    if(pressedButton > 0 && leftMousePressed)
    {
        //Get mouse position
        int x, y;
        windowGetMousePos(&x, &y);

        //Check if mouse is inside main window bounds
        if(uiIsMouseInsideMainWindow_powderTrain(&x, &y))
        {
            //Spawn particle
            particleSystemSpawnElement(pressedButton);
        }
    }
}

void particleSystemUpdate()
{
    //Iterate over particle array
        //Skip empty spots
        //Update full cells corresponding to their type
            //Reset color of old cell
            //Set color of new cell

    pixelRendererFlush();       
}

void particleSystemCleanUp()
{
    pixelRendererCleanUp();
}