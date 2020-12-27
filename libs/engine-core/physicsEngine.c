#include "physicsEngine.h"

void physicsEngineInit()
{
    //Create physics space
    space = cpSpaceNew();

    //Set gravity
    cpSpaceSetGravity(space, cpv(0, 100));

    //Create the ground as a static/non-movable shape
    groundShape = cpSegmentShapeNew(
        cpSpaceGetStaticBody(space),
        cpv(0, HEIGHT - 50),
        cpv(WIDTH, HEIGHT - 50),
        0
    ); 
    cpShapeSetFriction(groundShape, 1);
    cpSpaceAddShape(space, groundShape);

    boxBody = NULL; 
    boxShape = NULL;    
}   

unsigned int physicsEngineAddBox(float x, float y)
{
    //Initialize the box properties
    cpFloat boxWidth = 100;
    cpFloat boxHeight = 100;
    cpFloat boxMass = 1;
    cpFloat moment = cpMomentForBox(boxMass, boxWidth, boxHeight);

    //Create box body
    boxBody = cpSpaceAddBody(space, cpBodyNew(boxMass, moment));
    cpBodySetPosition(boxBody, cpv(x, y));

    //Create collision shape
    boxShape = cpSpaceAddShape(space, cpBoxShapeNew(boxBody, boxWidth, boxHeight, 0));
    cpShapeSetFriction(boxShape, 0.7);
}

void physicsEngineGetWorldtransform(float* position, float* rotation)
{
    cpVect pos = cpBodyGetPosition(boxBody);
    position[0] = (float)pos.x;
    position[1] = (float)pos.y;

    cpFloat rot = cpBodyGetAngle(boxBody);
    rotation[0] = rot;
}

void phyicsEnginePerFrame(float dt)
{
    cpSpaceStep(space, dt);
}

void physicsEngineCleanUp()
{
    //Free bodies
    cpBodyFree(boxBody);

    //Free shapes
    cpShapeFree(groundShape);
    cpShapeFree(boxShape);

    //Free space    
    cpSpaceFree(space);
}