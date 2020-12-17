#ifndef WINDOW
#define WINDOW

#include "../../vendor/loading/glad.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../../vendor/logging/log.h"
#include "errorManager.h"

// --- Variables ---
static SDL_Window *s_window;
static SDL_GLContext *s_context;
static SDL_Event s_event;   
static bool s_isRunning;
static char* s_windowName;
static char* s_frameRateBuffer;
static char* s_WindowTitleBuffer;
static int s_frameCounter;
static float s_dtAccumulated;
static char* s_drawCallBuffer;

#define WIDTH 1600
#define HEIGHT 900

extern long lastFrame;
extern float deltaTime;
extern bool leftMousePressed;
extern bool rightMousePressed;

// --- Functions ---
void windowInit();
bool windowIsRunning();
void windowPrepare();
void windowSwapBuffer();
void windowCleanUp();
void windowPollEvents();
void windowCalcFrametime();
void windowGetMousePos(int* x, int* y);
void windowSetMousePos(int x, int y);
void windowRenderTitle(int drawcalls);
static void windowHandleMouseClick(SDL_MouseButtonEvent* MBE);
static void windowPrepareframeRateBuffer();
static void windowPrepareDrawCallBuffer(int drawcalls);

#endif