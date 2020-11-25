#include "window.h"
   
void windowInit()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("SDL could not be initialized! SDL_Error: %s", SDL_GetError());
    else
        log_info("SDL initialized!");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    window = SDL_CreateWindow("RenderingEngine (Sandbox)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
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

    isRunning = true;
}

bool windowIsRunning()
{        
    return isRunning;
}

void windowPollEvents()
{
    SDL_PollEvent(&event);

    if(event.type == SDL_QUIT)
    {
        isRunning = false;
        log_info("Quitting!");
    }
    else if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            isRunning = false;
            log_info("Quitting!");
        }
    } 
}

void windowRender()
{
    GLCall(glClearColor(1.0, 1.0, 0.0, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    SDL_GL_SwapWindow(window);
}

void windowCleanUp()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}   