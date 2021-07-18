#include "particleSystem.h"

static bool cellIsDestroyable(int id)
{
    return particleLookUp[id].isDestroyable;
}

static bool cellisDestroyer(int id)
{
    return particleLookUp[id].isDestroyer;
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
        int cellAboveID = particleArray[new_y1][old_x][0];
        int cellUnderID = particleArray[new_y2][old_x][0];
        int cellLeftID = particleArray[old_y][new_x1][0];
        int cellRightID = particleArray[old_y][new_x2][0];

        if(cellisDestroyer(cellAboveID) || cellisDestroyer(cellUnderID) || cellisDestroyer(cellLeftID) || cellisDestroyer(cellRightID))
        {
            return true;
        }
    }

    return false;
}

static void spawnParticle(int mouse_x, int mouse_y, unsigned int id)
{
    //Check if mouse position is still in bounds
    if(mouse_x >= 0 && mouse_x < CANVAS_WIDTH && mouse_y >= 0 && mouse_y < CANVAS_HEIGHT)
    {
        //Get particle id
        int particleID = particleArray[mouse_y][mouse_x][0];

        //Only fill cell if it is empty
        if(particleID < 0)
        {
            //Add particle into particle array corresponding to mouse position
            particleArray[mouse_y][mouse_x][0] = id;

            //Set cell color depending on the spawned element
            pixelRendererSet(mouse_x, mouse_y, particleLookUp[id].color);
        }
    }    
}

static void despawnParticle(int x, int y)
{
    particleArray[y][x][0] = -1;
    particleArray[y][x][1] = 0;
    pixelRendererReset(x, y);
}
static void moveParticleToPos(int old_x, int old_y, int new_x, int new_y, int id)
{
    //Move particle to new cell and color new cell accordingly
    particleArray[new_y][new_x][0] = id;
    pixelRendererSet(new_x, new_y, particleLookUp[id].color);

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
                moveParticleToPos(x, y, x, y + 1, SAND_ID);
            }
            //Check if cell below is water
            else if(particleArray[y + 1][x][0] == WATER_ID)
            {
                //Move water particle one cell up
                moveParticleToPos(x, y + 1, x, y, WATER_ID);

                //Move sand particle to the free cell
                moveParticleToPos(x, y, x, y + 1, SAND_ID);
            }       
            //Check if cell right below is still in bounds and empty
            else if((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0))
            {
                //Move particle one cell down to the right
                moveParticleToPos(x, y, x + 1, y + 1, SAND_ID);
            }
            //Check if cell left below is still in bounds and empty
            else if((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0))
            {
                //Move particle one cell to the left
                moveParticleToPos(x, y, x - 1, y + 1, SAND_ID);
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
                moveParticleToPos(x, y, x, y + 1, WATER_ID);
            }        
            //Check if cell right below is still in bounds and empty
            else if((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0))
            {
                //Move particle one cell down to the right
                moveParticleToPos(x, y, x + 1, y + 1, WATER_ID);
            }
            //Check if cell left below is still in bounds and empty
            else if((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0))
            {
                //Move particle one cell to the left
                moveParticleToPos(x, y, x - 1, y + 1, WATER_ID);
            }   
            //Check if cell next to the right is still in bounds and empty
            else if((new_x2 < CANVAS_WIDTH) && (particleArray[y][x + 1][0] < 0))
            {
                //Move particle one cell to the right
                moveParticleToPos(x, y, x + 1, y, WATER_ID);
            }  
            //Check if cell next to the left is still in bounds and empty  
            else if((new_x1 >= 0) && (particleArray[y][x - 1][0] < 0))
            {
                //Move particle one cell to the left
                moveParticleToPos(x, y, x - 1, y, WATER_ID);
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
            moveParticleToPos(x, y, x, y + 1, ACID_ID);
        }  
        //Check if cell right below is still in bounds and empty or destroyable
        else if(((new_x2 < CANVAS_WIDTH) && (particleArray[y + 1][x + 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell down to the right
            moveParticleToPos(x, y, x + 1, y + 1, ACID_ID);
        }
        //Check if cell left below is still in bounds and empty or destroyable
        else if(((new_x1 >= 0) && (particleArray[y + 1][x - 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell to the left
            moveParticleToPos(x, y, x - 1, y + 1, ACID_ID);
        }   
        //Check if cell next to the right is still in bounds and empty or destroyable
        else if(((new_x2 < CANVAS_WIDTH) && (particleArray[y][x + 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell to the right
            moveParticleToPos(x, y, x + 1, y, ACID_ID);
        }  
        //Check if cell next to the left is still in bounds and empty or destroyable
        else if(((new_x1 >= 0) && (particleArray[y][x - 1][0] < 0)) || cellIsDestroyable(particleArray[y + 1][x][0]))
        {
            //Move particle one cell to the left
            moveParticleToPos(x, y, x - 1, y, ACID_ID);
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
            particleArray[i][j][0] = -1;    //ID
            particleArray[i][j][1] = 0;     //MoveFactor
        }
    }

    //Create particle look up table
    particle_t sand = {
        SAND_ID, {0.839f, 0.749f, 0.4f}, 50, true, false
    };
    particle_t water = {
        WATER_ID, {0.286f, 0.607f, 0.933f}, 50, true, false
    };
    particle_t stone = {
        STONE_ID, {0.541f, 0.541f, 0.541f}, 0, false, false
    };
    particle_t fire = {
        FIRE_ID, {0.941f, 0.094f, 0.0f}, 50, true, true
    };
    particle_t acid = {
        ACID_ID, {0.007f, 0.968f, 0.027f}, 50, false, true
    };
    particle_t wood = {
        WOOD_ID, {0.352f, 0.247f, 0.168f}, 0, true, false
    };

    particleLookUp[SAND_ID] = sand;
    particleLookUp[WATER_ID] = water;
    particleLookUp[STONE_ID] = stone;
    particleLookUp[FIRE_ID] = fire;
    particleLookUp[ACID_ID] = acid;
    particleLookUp[WOOD_ID] = wood;
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
            //Get particleID
            int particleID = particleArray[i][j][0];

            //If the cell is not empty
            if(particleID > 0)
            {
                //Update moveFactor according to particle type
                particleArray[i][j][1] += particleLookUp[particleID].moveFactor;

                //If the moveFactor reaches 100 => move particle
                if(particleArray[i][j][1] >= 100)
                {
                    //Check for different particle types
                    if(particleID == SAND_ID)
                    {
                        processSandParticle(j, i);
                    }
                    else if(particleID == WATER_ID)
                    {
                        processWaterParticle(j, i);
                    }
                    else if(particleID == ACID_ID)
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