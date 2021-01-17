#ifndef WINDOW2D
#define WINDOW2D

#include "../../../vendor/loading/glad.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../../../vendor/logging/log.h"
#include "../general/errorManager.h"

// --- Variables ---
static SDL_Window *window = NULL;
static SDL_GLContext *context = NULL;
static SDL_Event event;   
static bool isRunning = false;
static char* windowName = NULL;
static char* windowTitleBuffer = NULL;
static char* drawcallBuffer = NULL;

const extern unsigned int WIDTH;
const extern unsigned int HEIGHT;
extern long lastFrame;
extern float deltaTime;
extern bool leftMousePressed;
extern bool rightMousePressed;

// --- Functions ---
void windowInit(char* title);
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
void windowPrepareDrawcallBuffer(int drawcalls);

#endif