#include "physicsEngine2D.h"

void physicsEngineInit()
{
    //Create physics space
    space = cpSpaceNew();

    //Set gravity
    cpSpaceSetGravity(space, cpv(0, 100));

    //Create the ground as a static/non-movable shape
    groundShape = cpSegmentShapeNew(
        cpSpaceGetStaticBody(space),
        cpv(0 - 50, HEIGHT - 50),
        cpv(WIDTH - 350, HEIGHT - 50),
        0
    ); 
    cpShapeSetFriction(groundShape, 1);
    cpSpaceAddShape(space, groundShape);

    //Create left wall
    leftWallShape = cpSegmentShapeNew(
        cpSpaceGetStaticBody(space),
        cpv(0 - 50, HEIGHT - 50),
        cpv(0 - 50, 0 - 50),
        0
    ); 
    cpShapeSetFriction(leftWallShape, 1);
    cpSpaceAddShape(space, leftWallShape);

    //Create right wall
    rightWallShape = cpSegmentShapeNew(
        cpSpaceGetStaticBody(space),
        cpv(WIDTH - 350, HEIGHT - 50),
        cpv(WIDTH - 350, 0 - 50),
        0
    ); 
    cpShapeSetFriction(rightWallShape, 1);
    cpSpaceAddShape(space, rightWallShape);

    //Create ceiling
    ceilingShape = cpSegmentShapeNew(
        cpSpaceGetStaticBody(space),
        cpv(0 - 50, 0 - 50),
        cpv(WIDTH - 350, 0 - 50),
        0
    ); 
    cpShapeSetFriction(ceilingShape, 1);
    cpSpaceAddShape(space, ceilingShape);

    //Init boxes array
    for(int i = 0; i < MAX_PHYSICS_OBJECTS; i++)
    {
        boxes[i].boxShape = NULL;
        boxes[i].boxBody = NULL;
        boxes[i].slotUsed = false;
    }
}   

void physicsEngineAddBox(unsigned int id, float x, float y, float width, float height, float mass)
{
    //Initialize the box properties
    cpFloat moment = cpMomentForBox(mass, width, height);

    //Create box body
    cpBody* body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    cpBodySetPosition(body, cpv(x, y));

    //Create collision shape
    cpShape* shape = cpSpaceAddShape(space, cpBoxShapeNew(body, width, height, 0));
    cpShapeSetFriction(shape, 0.8);

    //Save box in array
    boxes[id].boxBody = body;
    boxes[id].boxShape = shape;
    boxes[id].slotUsed = true;

    physicsObjCounter++;
}

void physicsEngineGetWorldtransform(unsigned int id, float* position, float* rotation)
{
    if(id < MAX_PHYSICS_OBJECTS && boxes[id].slotUsed == true)
    {
        cpVect pos = cpBodyGetPosition(boxes[id].boxBody);
        position[0] = (float)pos.x;
        position[1] = (float)pos.y;

        cpFloat rot = cpBodyGetAngle(boxes[id].boxBody);
        rotation[0] = rot;
    }
    else
    {
        log_error("You are out of bounds of the physics object array!");
        log_error("Or you are referencing an element that does not exist!");
    }        
}

void phyicsEnginePerFrame(float dt)
{
    cpSpaceStep(space, dt);
}

void physicsEngineDeleteObject(unsigned int id)
{
    if(id < MAX_PHYSICS_OBJECTS && boxes[id].slotUsed == true)
    {
        cpBodyFree(boxes[id].boxBody);
        cpShapeFree(boxes[id].boxShape);
        physicsObjCounter--;
    }
    else
    {
        log_error("You are out of bounds of the physics object array!");
        log_error("Or you are referencing an element that does not exist!");
    }
}

void physicsEngineDeleteScene()
{
    //Free shapes
    cpShapeFree(groundShape);
    cpShapeFree(leftWallShape);
    cpShapeFree(rightWallShape);
    cpShapeFree(ceilingShape);

    //Free space    
    cpSpaceFree(space);
}

void physicsEngineCleanUp()
{    
    //Free bodies and shapes in box array
    for(int i = 0; i < MAX_PHYSICS_OBJECTS; i++)
    {
        if(physicsObjCounter > 0)
        {
            if(boxes[i].slotUsed == true)
            {
                cpBodyFree(boxes[i].boxBody);
                cpShapeFree(boxes[i].boxShape);
                 physicsObjCounter--;
            }        
        }
    }

    //Free shapes
    cpShapeFree(groundShape);
    cpShapeFree(leftWallShape);
    cpShapeFree(rightWallShape);
    cpShapeFree(ceilingShape);

    //Free space    
    cpSpaceFree(space);
}