#include "powderTrain/powderTrain.h"

int main()
{
    powderTrainInit();

    while(powderTrainIsRunning())
        powderTrainPerFrame();

    powderTrainCleanUp();
    return 0;    
}