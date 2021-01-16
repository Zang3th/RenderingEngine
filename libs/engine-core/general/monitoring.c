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
    textBatchRendererAddText("Frametime:      ms", 15.0f, HEIGHT - 40.0f, 0.7f);
    textBatchRendererAddText("FPS:" , 15.0f, HEIGHT - 80.0f, 0.7f);
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
    textSimpleRendererDisplay(&dtAccAvgBuffer[0], 170.0f, HEIGHT - 40.0f, 0.7f, (vec3){0.8f, 0.8f, 0.8f});
    textSimpleRendererDisplay(&fpsAvgBuffer[0], 75.0f, HEIGHT - 80.0f, 0.7f, (vec3){0.8f, 0.8f, 0.8f});
}

void monitoringCleanUp()
{
    free(dtAccAvgBuffer);
    free(fpsAvgBuffer);
}