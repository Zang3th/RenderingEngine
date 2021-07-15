#include "particleSystem.h"

static bool cellIsDestroyable(int index)
{
    return destroyableCellsLookUp[index];
}

static bool cellisDestroyer(int index)
{
    return destroyerCellsLookUp[index];
}

static bool destroyerCellisNearby(int old_x, int old_y)
{
    //Calculate parameters
    int new_x1 = old_x - 1;
    int new_x2 = old_x + 1;
    int new_y1 = old_y - 1;
    int new_y2 = old_y + 1;

    if(new_x1 >= 0 && new_x2 < CANVAS_WIDTH && new_y1 >= 0 && new_y1 < CANVAS_HEIGHT)
    {
        int cellAboveIndex = particleArray[new_y1][old_x][0];
        int cellUnderIndex = particleArray[new_y2][old_x][0];
        int cellLeftIndex = particleArray[old_y][new_x1][0];
        int cellRightIndex = particleArray[old_y][new_x2][0];

        if(cellisDestroyer(cellAboveIndex) || cellisDestroyer(cellUnderIndex) || cellisDestroyer(cellLeftIndex) || cellisDestroyer(cellRightIndex))
        {
            return true;
        }
    }

    return false;
}

static void spawnParticle(int mouse_x, int mouse_y, unsigned int index)
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

static void despawnParticle(int x, int y)
{
    particleArray[y][x][0] = -1;
    particleArray[y][x][1] = 0;
    pixelRendererReset(x, y);
}
static void moveParticleToPos(int old_x, int old_y, int new_x, int new_y, int index)
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

static void processSandParticle(int x, int y)
{
    //Calculate parameters
    int new_x1 = x - 1;
    int new_x2 = x + 1;
    int new_y = y + 1;

    //Check if cell below is still in bounds
    if(new_y < CANVAS_HEIGHT)
    {
        //Check if destroyer cell is nearby
        if(!destroyerCellisNearby(x, y))
        {
            //Check if cell below is empty or no destroyer
            if(particleArray[y + 1][x][0] < 0)
            {
                //Move particle one cell down
                moveParticleToPos(x, y, x, y + 1, SAND_INDEX);
            }
            //Check if cell below is water
            else if(particleArray[y + 1][x][0] == WATER_INDEX)
            {
                //Move water particle one cell up
                moveParticleToPos(x, y + 1, x, y, WATER_INDEX);

                //Move sand particle to the free cell
                moveParticleToPos(x, y, x, y + 1, SAND_INDEX);
            }       
            //Check if cell right below is still in bounds and empty
            else if((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0))
            {
                //Move particle one cell down to the right
                moveParticleToPos(x, y, x + 1, y + 1, SAND_INDEX);
            }
            //Check if cell left below is still in bounds and empty
            else if((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0))
            {
                //Move particle one cell to the left
                moveParticleToPos(x, y, x - 1, y + 1, SAND_INDEX);
            } 
        }
        else
        {
            despawnParticle(x, y);
        }      
    }  
}

static void processWaterParticle(int x, int y)
{
    //Calculate parameters
    int new_x1 = x - 1;
    int new_x2 = x + 1;
    int new_y = y + 1;

    //Check if cell below is still in bounds
    if(new_y < CANVAS_HEIGHT)
    {
        //Check if destroyer cell is nearby
        if(!destroyerCellisNearby(x, y))
        {
            //Check if cell below is empty
            if(particleArray[y + 1][x][0] < 0)
            {
                //Move particle one cell down
                moveParticleToPos(x, y, x, y + 1, WATER_INDEX);
            }        
            //Check if cell right below is still in bounds and empty
            else if((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0))
            {
                //Move particle one cell down to the right
                moveParticleToPos(x, y, x + 1, y + 1, WATER_INDEX);
            }
            //Check if cell left below is still in bounds and empty
            else if((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0))
            {
                //Move particle one cell to the left
                moveParticleToPos(x, y, x - 1, y + 1, WATER_INDEX);
            }   
            //Check if cell next to the right is still in bounds and empty
            else if((new_x2 < CANVAS_WIDTH) && (particleArray[y][x + 1][0] < 0))
            {
                //Move particle one cell to the right
                moveParticleToPos(x, y, x + 1, y, WATER_INDEX);
            }  
            //Check if cell next to the left is still in bounds and empty  
            else if((new_x1 >= 0) && (particleArray[y][x - 1][0] < 0))
            {
                //Move particle one cell to the left
                moveParticleToPos(x, y, x - 1, y, WATER_INDEX);
            } 
        }
        else
        {
            despawnParticle(x, y);
        }
    } 
}

static void processAcidParticle(int x, int y)
{
    //Calculate parameters
    int new_x1 = x - 1;
    int new_x2 = x + 1;
    int new_y = y + 1;

    //Check if cell below is still in bounds
    if(new_y < CANVAS_HEIGHT)
    {
        //Check if cell below is empty or destroyable
        if(particleArray[y + 1][x][0] < 0 || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell down
            moveParticleToPos(x, y, x, y + 1, ACID_INDEX);
        }  
        //Check if cell right below is still in bounds and empty or destroyable
        else if(((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell down to the right
            moveParticleToPos(x, y, x + 1, y + 1, ACID_INDEX);
        }
        //Check if cell left below is still in bounds and empty or destroyable
        else if(((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell to the left
            moveParticleToPos(x, y, x - 1, y + 1, ACID_INDEX);
        }   
        //Check if cell next to the right is still in bounds and empty or destroyable
        else if(((new_x2 < CANVAS_WIDTH) && (particleArray[y][x + 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell to the right
            moveParticleToPos(x, y, x + 1, y, ACID_INDEX);
        }  
        //Check if cell next to the left is still in bounds and empty or destroyable
        else if(((new_x1 >= 0) && (particleArray[y][x - 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell to the left
            moveParticleToPos(x, y, x - 1, y, ACID_INDEX);
        } 
    } 
}

void particleSystemInit()
{
    //Init pixel renderer
    pixelRendererInit("../res/textures/powderTrain/Background_1500x900.jpg");

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
            //Spawn 25 particles per click
            spawnParticle(x, y, pressedButton);
            for(int i = 0; i < 3; i++)
            {
                spawnParticle(x - getPseudoRandom_uint(5), y - getPseudoRandom_uint(5), pressedButton);
                spawnParticle(x, y - getPseudoRandom_uint(5), pressedButton);
                spawnParticle(x + getPseudoRandom_uint(5), y - getPseudoRandom_uint(5), pressedButton);
                spawnParticle(x - getPseudoRandom_uint(5), y, pressedButton);
                spawnParticle(x + getPseudoRandom_uint(5), y, pressedButton);
                spawnParticle(x - getPseudoRandom_uint(5), y + getPseudoRandom_uint(5), pressedButton);
                spawnParticle(x, y + getPseudoRandom_uint(5) , pressedButton);
                spawnParticle(x + getPseudoRandom_uint(5), y + getPseudoRandom_uint(5), pressedButton);
            }
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
                        processSandParticle(j, i);
                    }
                    else if(particleIndex == WATER_INDEX)
                    {
                        processWaterParticle(j, i);
                    }
                    else if(particleIndex == ACID_INDEX)
                    {
                        processAcidParticle(j, i);
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