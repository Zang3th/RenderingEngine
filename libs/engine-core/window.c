#include "window.h"
   
void windowInit()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    window = SDL_CreateWindow("RenderingEngine (Sandbox)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);
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
    }
}

void windowRender()
{
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void windowCleanUp()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}   