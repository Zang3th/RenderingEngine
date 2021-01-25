#include "meshCreator.h"

mesh_t* meshCreatorPlane(unsigned int size, float tileSize)
{
    //Amount of vertices, texture coordinates and indices
    unsigned int vAmount, tAmount, iAmount; 
    unsigned int squareAmount = size * size;

    vAmount = squareAmount * 4;
    tAmount = squareAmount * 4;
    iAmount = squareAmount * 6;

    //Create mesh
    mesh_t* mesh = createMesh(vAmount, tAmount, iAmount);    

    //Array indices
    unsigned int vIndex = 0;
    unsigned int tIndex = 0;
    unsigned int iIndex = 0;

    //Create vertices and texture coordinates
	for (int j = 0; j <= size; ++j)
	{
		for (int i = 0; i <= size; ++i)
		{            
            float xPos = (float)i;
            float yPos = 0.0f;
            float zPos = (float)j;

            //Save vertices
            if(vIndex + 2 < mesh->verticeCount)
            {
                mesh->vertices[vIndex] = xPos * tileSize;
                mesh->vertices[vIndex + 1] = yPos;
                mesh->vertices[vIndex + 2] = zPos * tileSize;

                vIndex += 3;
            }            

            //Save texture coordinates
            if(tIndex + 1 < mesh->texCoordsCount)
            {
                mesh->texCoords[tIndex] = xPos;
                mesh->texCoords[tIndex + 1] = zPos;

                tIndex += 2;
            }            

            //Save indices
            if(iIndex + 5 < mesh->indiceCount)
            {
                if ((j != size) && (i != size))
			    {
                    unsigned int row1 = j * (size + 1);
                    unsigned int row2 = (j + 1) * (size + 1);

                    //Triangle 1
                    mesh->indices[iIndex] = row1 + i;
                    mesh->indices[iIndex + 1] = row1 + i + 1;
                    mesh->indices[iIndex + 2] = row2 + i + 1;

                    //Triangle 2
                    mesh->indices[iIndex + 3] = row1 + i;
                    mesh->indices[iIndex + 4] = row2 + i + 1;
                    mesh->indices[iIndex + 5] = row2 + i; 

                    iIndex += 6;     
       
                }
            }  
		}
	}    

    return mesh;
}

mesh_t* meshCreatorOneTile()
{
    //Amount of vertices, texture coordinates and indices
    unsigned int vAmount = 4, tAmount = 4, iAmount = 6;

    //Create mesh
    mesh_t* mesh = createMesh(vAmount, tAmount, iAmount);

    //Create data
    float vertices[] =
    {
        //Position  
        0.0f, 0.0f, 0.0f,
        20.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 20.0f,
        20.0f, 0.0f, 20.0f
    };

    float texCoords[] = 
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        1, 2, 3
    };

    //Set data
    memcpy(&(mesh->vertices[0]), vertices, sizeof(vertices));
    memcpy(&(mesh->texCoords[0]), texCoords, sizeof(texCoords));
    memcpy(&(mesh->indices[0]), indices, sizeof(indices));

    return mesh;
}