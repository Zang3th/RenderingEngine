#ifndef WINDOW2D
#define WINDOW2D

#include "../../../vendor/loading/glad.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../../../vendor/logging/log.h"
#include "../general/errorManager.h"

// --- Variables ---
static SDL_Window *s_window;
static SDL_GLContext *s_context;
static SDL_Event s_event;   
static bool s_isRunning;
static char* s_windowName;
static char* s_WindowTitleBuffer;
static int s_frameCounter;
static char* s_drawCallBuffer;
static float s_dtAccumulated;

extern unsigned int WIDTH;
extern unsigned int HEIGHT;
extern float dtAccumulated_avg;
extern float framerate_avg;
extern long lastFrame;
extern float deltaTime;
extern bool leftMousePressed;
extern bool rightMousePressed;

// --- Functions ---
void windowInit();
bool windowIsRunning();
void windowPollEvents();
void windowHandleMouseClick(SDL_MouseButtonEvent* MBE);
void windowPrepare();
void windowSwapBuffer();
void windowCleanUp();
void windowCalcFrametime();
void windowGetMousePos(int* x, int* y);
void windowSetMousePos(int x, int y);
void windowUpdateTitle(int drawcalls);
void windowPrepareDrawCallBuffer(int drawcalls);

#endif