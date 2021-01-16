#ifndef WINDOW3D
#define WINDOW3D

#include "../../../vendor/loading/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "camera.h"
#include "../../../vendor/logging/log.h"
#include "../general/errorManager.h"

// --- Variables ---
static GLFWwindow* s_window;
static bool s_isRunning;
static char* s_windowName;
static char* s_WindowTitleBuffer;
static char* s_drawCallBuffer;

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
void windowPrepareDrawCallBuffer(int drawcalls);

#endif