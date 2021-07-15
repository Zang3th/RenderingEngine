#include "window.h"

//Init extern variables
GLFWwindow* window = NULL;  
bool isRunning = false;
const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool leftMousePressed = false;
bool rightMousePressed = false;
double lastX = 0.0f;
double lastY = 0.0f;

void windowInit(char* title)
{
    windowName = title;

    if(!glfwInit())
        log_error("GLFW could not be initialized! GLFW_Error: %d", glfwGetError(NULL));
    else
        log_info("GLFW initialized!");
        
    glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    

    window = glfwCreateWindow(WIDTH, HEIGHT, windowName, NULL, NULL);

    if(!window)
        log_error("Window could not be created! GLFW_Error: %d", glfwGetError(NULL));
    else
        log_info("GLFW Window created!");      

    glfwMakeContextCurrent(window);  
    glfwSwapInterval(0);

    if(!gladLoadGL()) 
        log_error("Couldn't load OpenGL via glad!");
    else   
        log_info("OpenGL %d.%d loaded via glad!", GLVersion.major, GLVersion.minor);
  
    GLCall(glViewport(0, 0, WIDTH, HEIGHT));  
	GLCall(glEnable(GL_MULTISAMPLE));    
    GLCall(glEnable(GL_BLEND)); //Enable blending to render transparent textures
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    windowTitleBuffer = malloc(sizeof(char) * 100);
    drawcallBuffer = malloc(sizeof(char) * 3);
   
    isRunning = true; //Start application
}

bool windowIsRunning()
{        
    return isRunning;
}

void windowPollEvents()
{
    rightMousePressed = false;
    glfwPollEvents();
}

void windowPrepare()
{
    GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void windowSwapBuffer()
{    
    glfwSwapBuffers(window);
}

void windowCleanUp()
{
    free(windowTitleBuffer);
    free(drawcallBuffer);
    
    glfwTerminate();   
}   

void windowCalcFrametime()
{   
    float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void windowGetMousePos(double* x, double* y)
{
    *x = lastX;
    *y = lastY;
}

void windowSetMousePos(double x, double y)
{
    glfwSetCursorPos(window, x, y);
}

void windowUpdateTitle(int drawcalls)
{
    strcpy(windowTitleBuffer, windowName);
    
    //Update window title buffer
    windowPrepareDrawcallBuffer(drawcalls);

    //Put buffer in action
    glfwSetWindowTitle(window, &windowTitleBuffer[0]);
}

void windowPrepareDrawcallBuffer(int drawcalls)
{
    strcat(windowTitleBuffer, " (Drawcalls: ");

    //Put drawcalls in the drawcall buffer
    int ret = snprintf(drawcallBuffer, 3, "%d", drawcalls);

    strcat(windowTitleBuffer, drawcallBuffer);
    strcat(windowTitleBuffer, ")");
}