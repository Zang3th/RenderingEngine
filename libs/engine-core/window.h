#ifndef WINDOW
#define WINDOW

#include "../../vendor/loading/glad.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../../vendor/logging/log.h"
#include "../engine-core/errorManager.h"

// --- Variables ---
static SDL_Window *s_window;
static SDL_GLContext *s_context;
static SDL_Event s_event;   
static bool s_isRunning;

#define WIDTH 1600
#define HEIGHT 900

extern long lastFrame;
extern float deltaTime;

//--- Functions ---
void windowInit();
bool windowIsRunning();
void windowPrepare();
void windowSwapBuffer();
void windowCleanUp();
void windowPollEvents();
void windowFrametime();

#endif