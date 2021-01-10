#include "window3D.h"

//Init static variables
static GLFWwindow* _window = NULL;
static bool _isRunning = false;

//Init extern variables
const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void windowInit()
{
    if(!glfwInit())
        log_error("GLFW could not be initialized! GLFW_Error: %d", glfwGetError(NULL));
    else
        log_info("GLFW initialized!");
        
    glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    

    _window = glfwCreateWindow(WIDTH, HEIGHT, "WrathGL", NULL, NULL);

    if(!_window)
        log_error("Window could not be created! GLFW_Error: %d", glfwGetError(NULL));
    else
        log_info("GLFW Window created!");      

    glfwMakeContextCurrent(_window);   
    glfwSwapInterval(0);   

    if(!gladLoadGL()) 
        log_error("Couldn't load OpenGL via glad!");
    else   
        log_info("OpenGL %d.%d loaded via glad!", GLVersion.major, GLVersion.minor);

    _isRunning = true;
    GLCall(glViewport(0, 0, WIDTH, HEIGHT));  
    GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_MULTISAMPLE));
}

bool windowIsRunning()
{
    return _isRunning;
}

void windowPollEvents()
{
    glfwPollEvents();
}

void windowProcessEvents()
{
    if(glfwWindowShouldClose(_window))
    {
        _isRunning = false; 
        log_info("Quitting!");
    }

    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, true);
        _isRunning = false; 
        log_info("Quitting!");
    }	      
}

void windowPrepare()
{
    GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void windowSwapBuffer()
{
    glfwSwapBuffers(_window);
}

void windowCleanUp()
{
    glfwTerminate();
}

void windowCalcFrametime()
{
    float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}