#ifndef WINDOW
#define WINDOW

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include "../../vendor/logging/log.h"
#include "../engine-core/errorManager.h"

// --- Variables ---
static SDL_Window *window;
static SDL_GLContext *context;
static SDL_Event event;   
static bool isRunning;

//--- Functions ---
void windowInit();

bool windowIsRunning();

void windowRender();

void windowCleanUp();

void windowPollEvents();

#endif