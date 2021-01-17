#include "monitoring.h"

//Init static variables
static float dtAccumulated_avg = 0.0f;
static float framerate_avg = 0.0f;
static int frameCounter = 0;
static float dtAccumulated = 0.0f;
static char* dtAccAvgBuffer = NULL;
static char* fpsAvgBuffer = NULL;

void monitoringInit()
{
    dtAccAvgBuffer = malloc(sizeof(float));
    fpsAvgBuffer = malloc(sizeof(float));
}

void monitoringAddText()
{
    textBatchRendererAddText("Frametime:      ms", 7.5f, HEIGHT - 25.0f, 0.5f);
    textBatchRendererAddText("FPS:" , 7.5f, HEIGHT - 50.0f, 0.5f);
}

void monitoringRenderText(float dt)
{  
    //Update monitoring variables
    frameCounter++; //Increment frame counter
    dtAccumulated += dt; //Accumulate dt

    if(frameCounter > 120) //Calculate avg framerate and frametime
    {
        framerate_avg = 1 / (dtAccumulated / frameCounter);
        dtAccumulated_avg = dtAccumulated / frameCounter;           

        frameCounter = 0;
        dtAccumulated = 0.0f;
    } 

    //Update buffers
    snprintf(&dtAccAvgBuffer[0], sizeof(dtAccAvgBuffer), "%2.2f", dtAccumulated_avg * 1000);
    snprintf(&fpsAvgBuffer[0], sizeof(fpsAvgBuffer), "%2.2f", framerate_avg);

    //Render updated buffers
    textSimpleRendererDisplay(&dtAccAvgBuffer[0], 120.0f, HEIGHT - 25.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});
    textSimpleRendererDisplay(&fpsAvgBuffer[0], 50.0f, HEIGHT - 50.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});
}

void monitoringCleanUp()
{
    free(dtAccAvgBuffer);
    free(fpsAvgBuffer);
}