#include "terrainEditor.h"

//Init extern variables
bool currentlyGenerating = false;

void terrainEditorGenerateNew(model_t* terrainModel, noise_t* noiseStruct)
{
    currentlyGenerating = true;

    //Edit noise parameter struct
    noiseStruct->roughness = random_float(0.03f);
    noiseStruct->octaves = 8;
    noiseStruct->divisor = 1.001f;
    noiseStruct->amplitude = random_float(1000.0f);

    //Create new terrain mesh 
    mesh_t* terrainMesh = meshCreatorTerrain(1000, 1.6f, noiseStruct); 

    //-----------------------------CRITICAL------------------------------

    //Delete old vao and ibo
    deleteIndexBuffer(terrainModel->ibo);
    deleteVertexArray(terrainModel->vao);

    //Assign vao and ibo out of the new mesh
    assignVAO(terrainModel, terrainMesh);    
    terrainModel->verticesToRender = terrainMesh->indiceCount;

    //-------------------------------------------------------------------

    //Delete new mesh
    deleteMesh(terrainMesh);

    currentlyGenerating = false;
}