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

    //Create vao out of new mesh
    unsigned int newVAO = createMeshVAO(terrainMesh);

    //Delete old vao and ibo
    deleteVertexArray(terrainModel->vao);

    //Change vao and ibo of the model
    terrainModel->vao = newVAO;
    terrainModel->verticesToRender = terrainMesh->indiceCount;

    //Delete new mesh
    deleteMesh(terrainMesh);

    currentlyGenerating = false;
}