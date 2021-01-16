#include "window3D.h"

//Init static variables
static GLFWwindow* s_window = NULL;
static bool s_isRunning = false;
static char* s_windowName = "RenderingEngine - WrathGL";
static char* s_WindowTitleBuffer = NULL;
static char* s_drawCallBuffer = NULL;

//Init extern variables
const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
camera_t* camera = NULL;

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

    s_window = glfwCreateWindow(WIDTH, HEIGHT, s_windowName, NULL, NULL);

    if(!s_window)
        log_error("Window could not be created! GLFW_Error: %d", glfwGetError(NULL));
    else
        log_info("GLFW Window created!");      

    glfwMakeContextCurrent(s_window);   
    glfwSwapInterval(1);   

    if(!gladLoadGL()) 
        log_error("Couldn't load OpenGL via glad!");
    else   
        log_info("OpenGL %d.%d loaded via glad!", GLVersion.major, GLVersion.minor);
    
    GLCall(glViewport(0, 0, WIDTH, HEIGHT));  
    GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_MULTISAMPLE));

    //Enable blending to render transparent textures
    GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    camera = cameraCreate((vec3){0.0f, 0.0f, 0.0f}, 0.0f, 90.0f);

    s_WindowTitleBuffer = malloc(sizeof(char) * 100);
    s_drawCallBuffer = malloc(sizeof(int));

    s_isRunning = true;
}

bool windowIsRunning()
{
    return s_isRunning;
}

void windowPollEvents()
{
    glfwPollEvents();
}

void windowProcessEvents()
{
    if(glfwWindowShouldClose(s_window))
    {
        s_isRunning = false; 
        log_info("Quitting!");
    }

    if(glfwGetKey(s_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(s_window, true);
        s_isRunning = false; 
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
    glfwSwapBuffers(s_window);
}

void windowCleanUp()
{
    free(s_WindowTitleBuffer);
    free(s_drawCallBuffer);

    glfwTerminate();
    cameraDestroy(camera);
}

void windowCalcFrametime()
{
    float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void windowUpdateTitle(int drawcalls)
{
    strcpy(s_WindowTitleBuffer, s_windowName);
    
    //Update window title buffer
    windowPrepareDrawCallBuffer(drawcalls);

    //Put buffer in action
    glfwSetWindowTitle(s_window, &s_WindowTitleBuffer[0]);
}

void windowPrepareDrawCallBuffer(int drawcalls)
{
    strcat(s_WindowTitleBuffer, " (Drawcalls: ");

    //Put drawcalls in the drawcall buffer
    int ret = snprintf(s_drawCallBuffer, sizeof(s_drawCallBuffer), "%d", drawcalls);

    strcat(s_WindowTitleBuffer, s_drawCallBuffer);
    strcat(s_WindowTitleBuffer, ")");
}