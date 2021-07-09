#include "particleSystem.h"

static void particleSystemMoveToPos(int old_x, int old_y, int new_x, int new_y, int index)
{
    //Move particle to new cell and color new cell accordingly
    particleArray[new_y][new_x][0] = index;
    pixelRendererSet(new_x, new_y, colorLookUp[index]);

    //Delete particle from old cell and reset old cell color
    particleArray[old_y][old_x][0] = -1;
    pixelRendererReset(old_x, old_y);

    //Reset move factor from old cell
    particleArray[old_y][old_x][1] = 0;
}

static void particleSystemProcessSandParticle(int x, int y)
{
    //Calculate parameters
    int new_x1 = x - 1;
    int new_x2 = x + 1;
    int new_y = y + 1;

    //Check if cell below is still in bounds
    if(new_y < CANVAS_HEIGHT)
    {
        //Check if cell below is empty
        if(particleArray[y + 1][x][0] < 0)
        {
            //Move particle one cell down
            particleSystemMoveToPos(x, y, x, y + 1, SAND_INDEX);
        }        
        //Check if cell right below is still in bounds and empty
        else if((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0))
        {
            //Move particle one cell down to the right
            particleSystemMoveToPos(x, y, x + 1, y + 1, SAND_INDEX);
        }
        //Check if cell left below is still in bounds and empty
        else if((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0))
        {
            //Move particle one cell to the left
            particleSystemMoveToPos(x, y, x - 1, y + 1, SAND_INDEX);
        }        
    }  
}

static void particleSystemProcessWaterParticle(int x, int y)
{
    //Calculate parameters
    int new_x1 = x - 1;
    int new_x2 = x + 1;
    int new_y = y + 1;

    //Check if cell below is still in bounds
    if(new_y < CANVAS_HEIGHT)
    {
        //Check if cell below is empty
        if(particleArray[y + 1][x][0] < 0)
        {
            //Move particle one cell down
            particleSystemMoveToPos(x, y, x, y + 1, WATER_INDEX);
        }        
        //Check if cell right below is still in bounds and empty
        else if((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0))
        {
            //Move particle one cell down to the right
            particleSystemMoveToPos(x, y, x + 1, y + 1, WATER_INDEX);
        }
        //Check if cell left below is still in bounds and empty
        else if((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0))
        {
            //Move particle one cell to the left
            particleSystemMoveToPos(x, y, x - 1, y + 1, WATER_INDEX);
        }   
        //Check if cell next to the right is still in bounds and empty
        else if((new_x2 < CANVAS_WIDTH) && (particleArray[y][x + 1][0] < 0))
        {
            //Move particle one cell to the right
            particleSystemMoveToPos(x, y, x + 1, y, WATER_INDEX);
        }  
        //Check if cell next to the left is still in bounds and empty  
        else if((new_x1 >= 0) && (particleArray[y][x - 1][0] < 0))
        {
            //Move particle one cell to the left
            particleSystemMoveToPos(x, y, x - 1, y, WATER_INDEX);
        } 
    } 
}

static void particleSystemSpawnElement(int mouse_x, int mouse_y, unsigned int index)
{
    //Check if mouse position is still in bounds
    if(mouse_x >= 0 && mouse_x < CANVAS_WIDTH && mouse_y >= 0 && mouse_y < CANVAS_HEIGHT)
    {
        //Get particle index
        int particleIndex = particleArray[mouse_y][mouse_x][0];

        //Only fill cell if it is empty
        if(particleIndex < 0)
        {
            //Add particle into particle array corresponding to mouse position
            particleArray[mouse_y][mouse_x][0] = index;

            //Set cell color depending on the spawned element
            pixelRendererSet(mouse_x, mouse_y, colorLookUp[index]);
        }
    }    
}

void particleSystemInit()
{
    //Init pixel renderer
    pixelRendererInit("res/textures/powderTrain/Background_1500x900.jpg");

    //Init particle array with -1 => empty slots
    for(int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for(int j = 0; j < CANVAS_WIDTH; j++)
        {
            particleArray[i][j][0] = -1;    //Index
            particleArray[i][j][1] = 0;     //MoveFactor
        }
    }
}

void particleSystemCheckSpawn()
{
    //Check for button press
    int pressedButton = uiGetPressedButton_powderTrain();

    //If a button is pressed and left mouse is hold 
    if(pressedButton > 0 && leftMousePressed)
    {
        //Get mouse position as double
        double mouse_x, mouse_y;
        window2DGetMousePos(&mouse_x, &mouse_y);
        //Cast to int cause we're working with pixels here
        int x = (int)mouse_x;
        int y = (int)mouse_y;

        //Check if mouse is inside main window bounds
        if(uiIsMouseInsideMainWindow_powderTrain(&mouse_x, &mouse_y))
        {
            //Spawn 17 particles per click
            particleSystemSpawnElement(x, y, pressedButton);
            particleSystemSpawnElement(x - getPseudoRandom_uint(5), y - getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x, y - getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x + getPseudoRandom_uint(5), y - getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x - getPseudoRandom_uint(5), y, pressedButton);
            particleSystemSpawnElement(x + getPseudoRandom_uint(5), y, pressedButton);
            particleSystemSpawnElement(x - getPseudoRandom_uint(5), y + getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x, y + getPseudoRandom_uint(5) , pressedButton);
            particleSystemSpawnElement(x + getPseudoRandom_uint(5), y + getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x - getPseudoRandom_uint(5), y - getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x, y - getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x + getPseudoRandom_uint(5), y - getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x - getPseudoRandom_uint(5), y, pressedButton);
            particleSystemSpawnElement(x + getPseudoRandom_uint(5), y, pressedButton);
            particleSystemSpawnElement(x - getPseudoRandom_uint(5), y + getPseudoRandom_uint(5), pressedButton);
            particleSystemSpawnElement(x, y + getPseudoRandom_uint(5) , pressedButton);
            particleSystemSpawnElement(x + getPseudoRandom_uint(5), y + getPseudoRandom_uint(5), pressedButton);
        }
    }
}

void particleSystemUpdate()
{
    for(int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for(int j = 0; j < CANVAS_WIDTH; j++)
        {
            //Get particleIndex
            int particleIndex = particleArray[i][j][0];

            //If the cell is not empty
            if(particleIndex > 0)
            {
                //Update moveFactor according to particle type
                particleArray[i][j][1] += moveFactorLookUp[particleIndex];

                //If the moveFactor reaches 100 => move particle
                if(particleArray[i][j][1] >= 100)
                {
                    //Check for different particle types
                    if(particleIndex == SAND_INDEX)
                    {
                        particleSystemProcessSandParticle(j, i);
                    }
                    else if(particleIndex == WATER_INDEX)
                    {
                        particleSystemProcessWaterParticle(j, i);
                    }
                }                
            }
        }
    }

    pixelRendererFlush();       
}

void particleSystemCleanUp()
{
    pixelRendererCleanUp();
}