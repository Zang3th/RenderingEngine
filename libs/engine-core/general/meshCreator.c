#include "meshCreator.h"

mesh_t* meshCreatorPlane(unsigned int size, float tileSize)
{
    //Amount of vertices and texture coordinates
    unsigned int vAmount, tAmount;    
    
    //Calculate needed amount
    if(size == 1)
    {
        vAmount = 4 * 3;
        tAmount = 4 * 2;
    }        
    else
    {
        vAmount = (size + 1) * (size + 1) * 3;
        tAmount = (size + 1) * (size + 1) * 2;
    }        

    //Create mesh
    mesh_t* mesh = meshCreate(vAmount, tAmount);

    //Array indices
    unsigned int vIndex = 0;
    unsigned int tIndex = 0;

    //Create vertices and texture coordinates
	for (int j = 0; j <= size; ++j)
	{
		for (int i = 0; i <= size; ++i)
		{            
            float xPos = (float)i;
            float yPos = 0.0f;
            float zPos = (float)j;

            //Save vertices
            mesh->vertices[vIndex] = xPos * tileSize;
            mesh->vertices[vIndex + 1] = yPos;
            mesh->vertices[vIndex + 2] = zPos * tileSize;

            //Save texture coordinates
            mesh->texCoords[tIndex] = xPos;
            mesh->texCoords[tIndex + 1] = zPos;

            /* log_info("x: %f, y: %f, z: %f", 
            mesh->vertices[vIndex], 
            mesh->vertices[vIndex + 1], 
            mesh->vertices[vIndex + 2]);

            log_info("tex1: %f, tex2: %f", 
            mesh->vertices[tIndex], 
            mesh->vertices[tIndex + 1]); */

            vIndex += 3;
            tIndex += 2;
		}
	}

    return mesh;
}