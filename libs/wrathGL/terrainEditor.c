#include "terrainEditor.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

//Init extern variables
bool currentlyGenerating = false;
bool finishedGenerating = false;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* terrainEditorStartThread(void* args)
{   
    threadArgs_t* threadArgs = (threadArgs_t*)args;  
    
    pthread_mutex_lock(&lock);  
    threadArgs->resultMesh = terrainEditorGenerateNew(threadArgs->noise);
    pthread_mutex_unlock(&lock);     

    currentlyGenerating = false;
    finishedGenerating = true;
    
    pthread_exit(NULL);
}

mesh_t* terrainEditorGenerateNew(noise_t* noiseStruct)
{
    //Randomize and edit noise parameter struct
    noiseStruct->roughness = random_float(0.03f);
    noiseStruct->octaves = 8;
    noiseStruct->divisor = 1.001f;
    noiseStruct->amplitude = random_float(1000.0f);
    
    //Create and assign new terrain mesh 
    mesh_t* newTerrainMesh = meshCreatorTerrain(1000, 1.6f, noiseStruct); 

    return newTerrainMesh;
}