#include "window2D.h"

static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    lastX = xpos;
    lastY = ypos;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
        leftMousePressed = true;
	}

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        leftMousePressed = false;
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
         rightMousePressed = true;
	}
}

static void process_events()
{
    if(glfwWindowShouldClose(window))
    {
        isRunning = false; 
        log_info("Quitting!");
    }

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        isRunning = false; 
        log_info("Quitting!");
    }
}

void window2DInit(char* title)
{
    windowInit(title);

    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

bool window2DIsRunning()
{        
    return windowIsRunning();
}

void window2DPollEvents()
{    
    windowPollEvents();
    process_events();
}

void window2DPrepare()
{
    windowPrepare();
}

void window2DSwapBuffer()
{    
    windowSwapBuffer();
}

void window2DCleanUp()
{
    windowCleanUp();   
}   

void window2DCalcFrametime()
{   
    windowCalcFrametime();
}

void window2DGetMousePos(double* x, double* y)
{
    windowGetMousePos(x, y);
}

void window2DSetMousePos(double x, double y)
{
    windowSetMousePos(x, y);
}

void window2DUpdateTitle(int drawcalls)
{
    windowUpdateTitle(drawcalls);
}

void window2DPrepareDrawcallBuffer(int drawcalls)
{
    windowPrepareDrawcallBuffer(drawcalls);
}