#ifndef WINDOW
#define WINDOW

#include "../../vendor/include/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "../../vendor/include/log.h"
#include "errorManager.h"
#include <stdlib.h>
#include <string.h>

// --- Variables ---
static char* windowName = NULL;
static char* windowTitleBuffer = NULL;
static char* drawcallBuffer = NULL;

extern GLFWwindow* window;  
extern bool isRunning;
const extern unsigned int WIDTH;
const extern unsigned int HEIGHT;
extern float deltaTime;
extern float lastFrame;
extern bool leftMousePressed;
extern bool rightMousePressed;
extern double lastX;
extern double lastY;

// --- Functions ---
void windowInit(char* title);
bool windowIsRunning();
void windowPollEvents();
void windowPrepare();
void windowSwapBuffer();
void windowCleanUp();
void windowCalcFrametime();
void windowGetMousePos(double* x, double* y);
void windowSetMousePos(double x, double y);
void windowUpdateTitle(int drawcalls);
void windowPrepareDrawcallBuffer(int drawcalls);

#endif