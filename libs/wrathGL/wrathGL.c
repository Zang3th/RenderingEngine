#include "wrathGL.h"

void wrathGLInit()
{
    //Init modules
    windowInit("RenderingEngine - WrathGL");   
    rendererInit();

    //Load resources
    resourceManagerLoadTexture("dirtTexture", "res/textures/wrathGL/Dirt.jpg"); 
    resourceManagerLoadTexture("grassTexture", "res/textures/wrathGL/Grass.jpg"); 
    resourceManagerLoadTexture("stoneTexture", "res/textures/wrathGL/Stone.jpeg");   
    resourceManagerLoadTexture("snowTexture", "res/textures/wrathGL/Snow.jpeg");     
    resourceManagerLoadShader("terrainShader", "res/shader/wrathGL/terrain_vs.glsl", "res/shader/wrathGL/terrain_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "res/shader/sandbox/batchText_vs.glsl", "res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "res/shader/sandbox/simpleText_vs.glsl", "res/shader/sandbox/simpleText_fs.glsl");

    //Get resources
    unsigned int* dirtTexture = resourceManagerGetTexture("dirtTexture");
    unsigned int* grassTexture = resourceManagerGetTexture("grassTexture");
    unsigned int* stoneTexture = resourceManagerGetTexture("stoneTexture");
    unsigned int* snowTexture = resourceManagerGetTexture("snowTexture");
    unsigned int* terrainShader = resourceManagerGetShader("terrainShader");

    //Create plane      
    mesh_t* mesh = meshCreatorTerrain(1000, 1.3);    
    //mesh_t* mesh = meshCreatorOneTile();
    //debugMesh(mesh);
    planeModel = createTerrainModel(mesh, terrainShader, dirtTexture, grassTexture, stoneTexture, snowTexture);
  
    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 different characters!
        textRenderingSystemsInit(resourceManagerGetShader("batchTextShader"), resourceManagerGetShader("simpleTextShader"));
        monitoringInit();  

        //Add static text
        monitoringAddText();
        wrathGLAddText();

        //After all text got added -> create one big buffer out of it, to render all batched text in one drawcall
        textBatchRendererUploadToGPU(); 
}

bool wrathGLIsRunning()
{
    return windowIsRunning();
}

void wrathGLAddText()
{
    textBatchRendererAddText("Position:", 7.5f, HEIGHT - 75.0f, 0.5f);
    textBatchRendererAddText("X:", 20.0f, HEIGHT - 100.0f, 0.5f);
    textBatchRendererAddText("Y:", 20.0f, HEIGHT - 125.0f, 0.5f);
    textBatchRendererAddText("Z:", 20.0f, HEIGHT - 150.0f, 0.5f);
    textBatchRendererAddText("Rotation:" , 7.5f, HEIGHT - 175.0f, 0.5f);
    textBatchRendererAddText("Yaw:" , 20.0f, HEIGHT - 200.0f, 0.5f);
    textBatchRendererAddText("Pitch:" , 20.0f, HEIGHT - 225.0f, 0.5f);
    textBatchRendererAddText("Vertices:" , 7.5f, HEIGHT - 250.0f, 0.5f);
}

void wrathGLRenderText()
{   
    //Create buffers
    char xBuffer[6];
    char yBuffer[6];
    char zBuffer[6];
    char yawBuffer[6];
    char pitchBuffer[5];
    char verticeBuffer[8];

    //Update buffers
    snprintf(&xBuffer[0], sizeof(xBuffer), "%4.f", camera->position[0]);   //X
    snprintf(&yBuffer[0], sizeof(yBuffer), "%4.f", camera->position[1]);   //Y
    snprintf(&zBuffer[0], sizeof(zBuffer), "%4.f", camera->position[2]);   //Z
    snprintf(&yawBuffer[0], sizeof(yawBuffer), "%3.f", camera->yaw);       //Yaw
    snprintf(&pitchBuffer[0], sizeof(pitchBuffer), "%2.f", camera->pitch); //Pitch
    snprintf(&verticeBuffer[0], sizeof(verticeBuffer), "%7d", vertices);   //Vertices

    //Render buffers
    textSimpleRendererDisplay(&xBuffer[0], 40.0f, HEIGHT - 100.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});     //X
    textSimpleRendererDisplay(&yBuffer[0], 40.0f, HEIGHT - 125.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});     //Y
    textSimpleRendererDisplay(&zBuffer[0], 40.0f, HEIGHT - 150.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});     //Z
    textSimpleRendererDisplay(&yawBuffer[0], 70.0f, HEIGHT - 200.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});   //Yaw
    textSimpleRendererDisplay(&pitchBuffer[0], 75.0f, HEIGHT - 225.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f}); //Pitch
    textSimpleRendererDisplay(&verticeBuffer[0], 20.0f, HEIGHT - 275.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f}); //Vertices
}

void wrathGLPerFrame()
{
    // --- Pre render
        windowCalcFrametime();
        windowPollEvents();
        windowProcessEvents();
        windowPrepare();         

    // --- Do render
        // -- Reset stats for current frame
        drawcalls = 0; 
        vertices = 0;
        if(wireframeMode == true){
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));}
        renderSimpleModel(planeModel);
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

        GLCall(glDisable(GL_DEPTH_TEST));
        textBatchRendererDisplay(); 
        monitoringRenderText(deltaTime);
        wrathGLRenderText();
        GLCall(glEnable(GL_DEPTH_TEST));

    // --- After render
        windowUpdateTitle(drawcalls);
        windowSwapBuffer(); 
}

void wrathGLCleanUp()
{
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    resourceManagerCleanUp(); 
    deleteModel(planeModel);
    windowCleanUp(); 
}