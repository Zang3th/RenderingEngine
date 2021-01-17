#ifndef WINDOW3D
#define WINDOW3D

#include "../../../vendor/loading/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "camera.h"
#include "../../../vendor/logging/log.h"
#include "../general/errorManager.h"

// --- Variables ---
static GLFWwindow* window;
static bool isRunning;
static char* windowName;
static char* windowTitleBuffer;
static char* drawcallBuffer;
static float lastX;
static float lastY;
static bool windowInFocus;

const extern unsigned int WIDTH;
const extern unsigned int HEIGHT;
extern float deltaTime;
extern float lastFrame;
extern camera_t* camera;

// --- Functions ---
void windowInit();
bool windowIsRunning();
void windowPollEvents();
void windowProcessEvents();
void windowPrepare();
void windowSwapBuffer();
void windowCleanUp();
void windowCalcFrametime();
void windowUpdateTitle(int drawcalls);
void windowPrepareDrawcallBuffer(int drawcalls);

#endif