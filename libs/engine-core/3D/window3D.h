#ifndef WINDOW3D
#define WINDOW3D

#include "../../../vendor/loading/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "../../../vendor/logging/log.h"
#include "../general/errorManager.h"

// --- Variables ---
static GLFWwindow* _window;
static bool _isRunning;

const extern unsigned int WIDTH;
const extern unsigned int HEIGHT;
extern float deltaTime;
extern float lastFrame;

// --- Functions ---
void windowInit();
bool windowIsRunning();
void windowPollEvents();
void windowProcessEvents();
void windowPrepare();
void windowSwapBuffer();
void windowCleanUp();
void windowCalcFrametime();

#endif