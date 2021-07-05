#include "window2D.h"

//Init extern variables
const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;
long lastFrame = 0;
float deltaTime = 0.0f;
bool leftMousePressed = false;
bool rightMousePressed = false;

void windowInit(char* title)
{
    windowName = title;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("SDL could not be initialized! SDL_Error: %s", SDL_GetError());
    else
        log_info("SDL initialized!");

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL)
        log_error("Window could not be created! SDL_Error: %s", SDL_GetError());
    else
        log_info("SDL Window created!");

    context = SDL_GL_CreateContext(window);
    if(context == NULL)
        log_error("Context could not be created! SDL_Error: %s", SDL_GetError());
    else
        log_info("Created context!");
    
    if(SDL_GL_MakeCurrent(window, context) < 0) 
        log_error("Context could not be made current! SDL_Error: %s", SDL_GetError());
    else
        log_info("Context made current!");         

    if(!gladLoadGL()) 
        log_error("Couldn't load OpenGL via glad!");
    else   
        log_info("OpenGL %d.%d loaded via glad!", GLVersion.major, GLVersion.minor);

    isRunning = true;
    SDL_GL_SetSwapInterval(1);

    windowTitleBuffer = malloc(sizeof(char) * 100);
    drawcallBuffer = malloc(sizeof(char) * 3);

    //Enable blending to render transparent textures
    GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

bool windowIsRunning()
{        
    return isRunning;
}

void windowPollEvents()
{
    while(SDL_PollEvent(&event))
    {
        leftMousePressed = false; 
        rightMousePressed = false;

        switch(event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                log_info("Quitting!");
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    isRunning = false;
                    log_info("Quitting!");
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                windowHandleMouseClick(&event.button);                    
                break;       
        }
    }
}

void windowHandleMouseClick(SDL_MouseButtonEvent* MBE)
{
  if(MBE->button == SDL_BUTTON_LEFT)  
    leftMousePressed = true;
  else if(MBE->button == SDL_BUTTON_RIGHT)
    rightMousePressed = true;  
}

void windowPrepare()
{
    GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void windowSwapBuffer()
{    
    SDL_GL_SwapWindow(window);
}

void windowCleanUp()
{
    free(windowTitleBuffer);
    free(drawcallBuffer);
    
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();    
}   

void windowCalcFrametime()
{   
    long currentFrame = SDL_GetTicks();
    deltaTime = ((float)(currentFrame - lastFrame)) / 1000;
    lastFrame = currentFrame;
}

void windowGetMousePos(int* x, int* y)
{
    SDL_GetMouseState(x, y);
}

void windowSetMousePos(int x, int y)
{
    SDL_WarpMouseInWindow(window, x, y);
}

void windowUpdateTitle(int drawcalls)
{
    strcpy(windowTitleBuffer, windowName);
    
    //Update window title buffer
    windowPrepareDrawcallBuffer(drawcalls);

    //Put buffer in action
    SDL_SetWindowTitle(window, &windowTitleBuffer[0]);
}

void windowPrepareDrawcallBuffer(int drawcalls)
{
    strcat(windowTitleBuffer, " (Drawcalls: ");

    //Put drawcalls in the drawcall buffer
    int ret = snprintf(drawcallBuffer, 3, "%d", drawcalls);

    strcat(windowTitleBuffer, drawcallBuffer);
    strcat(windowTitleBuffer, ")");
}