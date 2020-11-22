#ifndef WINDOW
#define WINDOW

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>

// --- Variables ---
SDL_Window *window;
SDL_GLContext *context;
SDL_Event event;   
bool isRunning;

//--- Functions ---
void windowInit();

bool windowIsRunning();

void windowRender();

void windowCleanUp();

void windowPollEvents();

#endif