#ifndef WINDOW3D
#define WINDOW3D

#include "../../../vendor/loading/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "../general/camera.h"
#include "../../../vendor/logging/log.h"
#include "../general/errorManager.h"

// --- Variables ---
static GLFWwindow* window = NULL;
static char* windowName = NULL;
static bool isRunning = false;
static char* windowTitleBuffer = NULL;
static char* drawcallBuffer = NULL;
static float lastX = 0.0f;
static float lastY = 0.0f;
static bool windowInFocus = false;

const extern unsigned int WIDTH;
const extern unsigned int HEIGHT;
extern float deltaTime;
extern float lastFrame;
extern camera_t* camera;
extern bool wireframeMode;
extern bool generateNewTerrain;

// --- Functions ---
void windowInit(char* title);
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