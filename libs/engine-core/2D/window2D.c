#include "window2D.h"

//Init static variables
static SDL_Window *s_window = NULL;
static SDL_GLContext *s_context = NULL;
static bool s_isRunning = false;
static char* s_windowName = "RenderingEngine - Sandbox";
static char* s_WindowTitleBuffer = NULL;
static int s_frameCounter = 0;
static char* s_drawCallBuffer = NULL;
static float s_dtAccumulated = 0.0f;

//Init extern variables
unsigned int WIDTH = 1600;
unsigned int HEIGHT = 900;
float dtAccumulated_avg = 0.0f;
float framerate_avg = 0.0f;
long lastFrame = 0;
float deltaTime = 0.0f;
bool leftMousePressed = false;
bool rightMousePressed = false;

void windowInit()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("SDL could not be initialized! SDL_Error: %s", SDL_GetError());
    else
        log_info("SDL initialized!");

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    s_window = SDL_CreateWindow(s_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if(s_window == NULL)
        log_error("Window could not be created! SDL_Error: %s", SDL_GetError());
    else
        log_info("SDL Window created!");

    s_context = SDL_GL_CreateContext(s_window);
    if(s_context == NULL)
        log_error("Context could not be created! SDL_Error: %s", SDL_GetError());
    else
        log_info("Created context!");
    
    if(SDL_GL_MakeCurrent(s_window, s_context) < 0) 
        log_error("Context could not be made current! SDL_Error: %s", SDL_GetError());
    else
        log_info("Context made current!");         

    if(!gladLoadGL()) 
        log_error("Couldn't load OpenGL via glad!");
    else   
        log_info("OpenGL %d.%d loaded via glad!", GLVersion.major, GLVersion.minor);

    s_isRunning = true;
    SDL_GL_SetSwapInterval(1);

    s_WindowTitleBuffer = malloc(sizeof(char) * 100);
    s_drawCallBuffer = malloc(sizeof(int));

    //Enable blending to render transparent textures
    GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

bool windowIsRunning()
{        
    return s_isRunning;
}

void windowPollEvents()
{
    while(SDL_PollEvent(&s_event))
    {
        leftMousePressed = false; 
        rightMousePressed = false;

        switch(s_event.type)
        {
            case SDL_QUIT:
                s_isRunning = false;
                log_info("Quitting!");
                break;

            case SDL_KEYDOWN:
                switch(s_event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    s_isRunning = false;
                    log_info("Quitting!");
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                windowHandleMouseClick(&s_event.button);                    
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
    SDL_GL_SwapWindow(s_window);
}

void windowCleanUp()
{
    free(s_WindowTitleBuffer);
    free(s_drawCallBuffer);
    
    SDL_GL_DeleteContext(s_context);
    SDL_DestroyWindow(s_window);
    SDL_Quit();    
}   

void windowCalcFrametime()
{   
    long currentFrame = SDL_GetTicks();
    
    if(currentFrame > lastFrame)
    {
       deltaTime = ((float)(currentFrame - lastFrame)) / 1000;
       lastFrame = currentFrame;

       s_frameCounter++; //Increment frame counter
       s_dtAccumulated += deltaTime; //Accumulate time to render current frame 

       if(s_frameCounter > 120) //Calculate framerate and draw it in the titlebar
       {
           //Put framerate in the framerate buffer
           framerate_avg = 1 / (s_dtAccumulated / s_frameCounter);
           dtAccumulated_avg = s_dtAccumulated / s_frameCounter;           

           s_frameCounter = 0;
           s_dtAccumulated = 0.0f;
       }    
    }
}

void windowGetMousePos(int* x, int* y)
{
    SDL_GetMouseState(x, y);
}

void windowSetMousePos(int x, int y)
{
    SDL_WarpMouseInWindow(s_window, x, y);
}

void windowUpdateTitle(int drawcalls)
{
    strcpy(s_WindowTitleBuffer, s_windowName);
    
    //Update window title buffer
    windowPrepareDrawCallBuffer(drawcalls);

    //Put buffer in action
    SDL_SetWindowTitle(s_window, &s_WindowTitleBuffer[0]);
}

void windowPrepareDrawCallBuffer(int drawcalls)
{
    strcat(s_WindowTitleBuffer, " (Drawcalls: ");

    //Put drawcalls in the drawcall buffer
    int ret = snprintf(s_drawCallBuffer, sizeof(s_drawCallBuffer), "%d", drawcalls);

    strcat(s_WindowTitleBuffer, s_drawCallBuffer);
    strcat(s_WindowTitleBuffer, ")");
}