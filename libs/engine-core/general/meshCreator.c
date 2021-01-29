#include "meshCreator.h"

void calculateNormals(mesh_t* mesh)
{
    //Iterate over all indices
    for(int i = 0; i+2 < mesh->indiceCount; i++)
    {
        //Get all indices for one triangle -> multiplied by 3 because one vertice consists out of 3 floats
        int index0 = mesh->indices[i] * 3;
        int index1 = mesh->indices[i + 1] * 3;
        int index2 = mesh->indices[i + 2] * 3;

        //Get all points of the triangle
        float p0_x = mesh->vertices[index0];     
        float p0_y = mesh->vertices[index0 + 1];
        float p0_z = mesh->vertices[index0 + 2];

        float p1_x = mesh->vertices[index1];      
        float p1_y = mesh->vertices[index1 + 1];
        float p1_z = mesh->vertices[index1 + 2];

        float p2_x = mesh->vertices[index2];       
        float p2_y = mesh->vertices[index2 + 1];                   
        float p2_z = mesh->vertices[index2 + 2];
        
        //Calculate the u vector
        float u0 = p1_x - p0_x;
        float u1 = p1_y - p0_y;
        float u2 = p1_z - p0_z;
        vec3 U = {u0, u1, u2};

        //Calculate the v vector
        float v0 = p2_x - p0_x;
        float v1 = p2_y - p0_y;
        float v2 = p2_z - p0_z;
        vec3 V = {v0, v1, v2};

        //Calculate cross product
        vec3 P;
        glm_cross(U, V, P);

        //Add normal to all precalculated normals of the vertice, normalize it and switch y-axis
        float p0_x_n = mesh->normals[index0] + P[0];
        float p0_y_n = mesh->normals[index0 + 1] + P[1] * (-1);
        float p0_z_n = mesh->normals[index0 + 2] + P[2];    
        vec3 P0 = {p0_x_n, p0_y_n, p0_z_n};
        glm_normalize(P0);

        float p1_x_n = mesh->normals[index1] + P[0];
        float p1_y_n = mesh->normals[index1 + 1] + P[1] * (-1);
        float p1_z_n = mesh->normals[index1 + 2] + P[2];    
        vec3 P1 = {p1_x_n, p1_y_n, p1_z_n};
        glm_normalize(P1);

        float p2_x_n = mesh->normals[index2] + P[0];
        float p2_y_n = mesh->normals[index2 + 1] + P[1] * (-1);
        float p2_z_n = mesh->normals[index2 + 2] + P[2];    
        vec3 P2 = {p2_x_n, p2_y_n, p2_z_n};
        glm_normalize(P2);

        //Save normals in array
        mesh->normals[index0] = P0[0];
        mesh->normals[index0 + 1] = P0[1];
        mesh->normals[index0 + 2] = P0[2];

        mesh->normals[index1] = P1[0];
        mesh->normals[index1 + 1] = P1[1];
        mesh->normals[index1 + 2] = P1[2];

        mesh->normals[index2] = P2[0];
        mesh->normals[index2 + 1] = P2[1];
        mesh->normals[index2 + 2] = P2[2];
    }
}

mesh_t* meshCreatorTerrain(unsigned int size, float tileSize)
{
    //Amount of vertices, texture coordinates and indices
    unsigned int vAmount, tAmount, iAmount; 

    //Calculate amounts
    vAmount = (size + 1) * (size + 1);
    tAmount = (size + 1) * (size + 1);
    iAmount = size * size;

    //Create mesh
    mesh_t* mesh = createMesh(vAmount, tAmount, iAmount);    

    //Array indices
    unsigned int vertexIndex = 0;
    unsigned int texCoordsIndex = 0;
    unsigned int indiceIndex = 0;
    unsigned int colorIndex = 0;
    unsigned int texSamplerIndex = 0;

    //Create vertices and texture coordinates
	for (int j = 0; j <= size; ++j)
	{
		for (int i = 0; i <= size; ++i)
		{            
            float xPos = (float)i;            
            float zPos = (float)j;
            //float yPos = getNoisePseudoRandom(xPos, zPos, 0.02, 10.0f);
            float yPos = getNoisePerlin2D(xPos, zPos, 0.008f, 8.0f, 1.001f);

            //Save vertices
            if(vertexIndex + 2 < mesh->verticeCount)
            {
                mesh->vertices[vertexIndex] = xPos * tileSize;
                mesh->vertices[vertexIndex + 1] = yPos;
                mesh->vertices[vertexIndex + 2] = zPos * tileSize;

                vertexIndex += 3;
            }            

            //Save texture coordinates
            if(texCoordsIndex + 1 < mesh->texCoordsCount)
            {
                mesh->texCoords[texCoordsIndex] = xPos;
                mesh->texCoords[texCoordsIndex + 1] = zPos;

                texCoordsIndex += 2;
            }            

            //Save indices
            if(indiceIndex + 5 < mesh->indiceCount)
            {
                if ((j != size) && (i != size))
			    {
                    unsigned int row1 = j * (size + 1);
                    unsigned int row2 = (j + 1) * (size + 1);

                    //Triangle 1
                    mesh->indices[indiceIndex] = row1 + i;
                    mesh->indices[indiceIndex + 1] = row1 + i + 1;
                    mesh->indices[indiceIndex + 2] = row2 + i + 1;

                    //Triangle 2
                    mesh->indices[indiceIndex + 3] = row1 + i;
                    mesh->indices[indiceIndex + 4] = row2 + i + 1;
                    mesh->indices[indiceIndex + 5] = row2 + i; 

                    indiceIndex += 6;  
                }
            } 

            //Save colors and corresponding texture indices
            if(colorIndex + 2 < mesh->colorCount)
            {
                if(yPos > 200.0f)                               //White
                {
                    mesh->colors[colorIndex] = 1.0f;
                    mesh->colors[colorIndex + 1] = 1.0f;
                    mesh->colors[colorIndex + 2] = 1.0f;

                    colorIndex += 3;

                    if(texSamplerIndex < mesh->texIndexCount)   //Snow texture
                    {
                        unsigned int texIndex = 3;
                        mesh->textureIndex[texSamplerIndex] = (float)texIndex;
                        texSamplerIndex++;
                    }
                }
                else if(yPos > 130.0f && yPos < 200.0f)         //Grey -> gradient
                {
                    mesh->colors[colorIndex] = -0.6 + (yPos / 160.0f);
                    mesh->colors[colorIndex + 1] = -0.6 + (yPos / 160.0f);
                    mesh->colors[colorIndex + 2] = -0.6 + (yPos / 160.0f);

                    colorIndex += 3;

                    if(texSamplerIndex < mesh->texIndexCount)   //Stone texture
                    {
                        mesh->textureIndex[texSamplerIndex] = 2.0f;
                        texSamplerIndex++;
                    }
                }
                else if(yPos > 100.0f && yPos < 130.0f)         //Green -> gradient
                {
                    mesh->colors[colorIndex] = -0.4 + (yPos / 160.0f);
                    mesh->colors[colorIndex + 1] = -0.2 + (yPos / 145.0f);
                    mesh->colors[colorIndex + 2] = -0.6 + (yPos / 145.0f);

                    colorIndex += 3;

                    if(texSamplerIndex < mesh->texIndexCount)   //Grass texture
                    {
                        mesh->textureIndex[texSamplerIndex] = 1.0f;
                        texSamplerIndex++;
                    }
                }     
                else                                            //Brown
                {
                    mesh->colors[colorIndex] = 0.44f;
                    mesh->colors[colorIndex + 1] = 0.41f;
                    mesh->colors[colorIndex + 2] = 0.23f;    

                    colorIndex += 3;

                    if(texSamplerIndex < mesh->texIndexCount)   //Dirt texture
                    {
                        mesh->textureIndex[texSamplerIndex] = 0.0f;
                        texSamplerIndex++;
                    }
                }
            } 
		}
	}    

    calculateNormals(mesh);
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

    float colors[] =
    { 
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    float normals[] =
    { 
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    //Set data
    memcpy(&(mesh->vertices[0]), vertices, sizeof(vertices));
    memcpy(&(mesh->texCoords[0]), texCoords, sizeof(texCoords));
    memcpy(&(mesh->indices[0]), indices, sizeof(indices));
    memcpy(&(mesh->colors[0]), colors, sizeof(colors));
    memcpy(&(mesh->normals[0]), normals, sizeof(normals));

    return mesh;
}