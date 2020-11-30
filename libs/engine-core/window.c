#include "window.h"
   
void windowInit()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("SDL could not be initialized! SDL_Error: %s", SDL_GetError());
    else
        log_info("SDL initialized!");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    s_window = SDL_CreateWindow("RenderingEngine (Sandbox)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
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
        log_info("OpenGL loaded via glad!");

    s_isRunning = true;
}

bool windowIsRunning()
{        
    return s_isRunning;
}

void windowPollEvents()
{
    SDL_PollEvent(&s_event);

    if(s_event.type == SDL_QUIT)
    {
        s_isRunning = false;
        log_info("Quitting!");
    }
    else if(s_event.type == SDL_KEYDOWN)
    {
        switch(s_event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            s_isRunning = false;
            log_info("Quitting!");
        }
    } 
}

void windowRender()
{
    GLCall(glClearColor(1.0, 1.0, 0.0, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    SDL_GL_SwapWindow(s_window);
}

void windowCleanUp()
{
    SDL_GL_DeleteContext(s_context);
    SDL_DestroyWindow(s_window);
    SDL_Quit();
}   