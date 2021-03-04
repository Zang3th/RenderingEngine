#include "window3D.h"

//Init extern variables
const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
camera_t* camera = NULL;
bool wireframeMode = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(windowInFocus)
    {
        float xOffset = xpos - lastX;
        float yOffset = lastY - ypos; //Reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;
        cameraProcessMouse(camera, xOffset, yOffset);
    }   
    else
    {
        lastX = xpos;
        lastY = ypos;
    } 
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		windowInFocus = true;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		windowInFocus = false;
	}
}

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    

    if(!gladLoadGL()) 
        log_error("Couldn't load OpenGL via glad!");
    else   
        log_info("OpenGL %d.%d loaded via glad!", GLVersion.major, GLVersion.minor);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    GLCall(glViewport(0, 0, WIDTH, HEIGHT));  
    GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_MULTISAMPLE));    
    GLCall(glEnable(GL_BLEND)); //Enable blending to render transparent textures
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    camera = cameraCreate((vec3){-293.0f, 1275.0f, 607.0f}, 0.0f, -57.0f); //Create camera

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
    glfwPollEvents();
}

void windowProcessEvents()
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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraProcessKeyboard(camera, FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraProcessKeyboard(camera, BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraProcessKeyboard(camera, RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraProcessKeyboard(camera, LEFT, deltaTime);	

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraProcessKeyboard(camera, UP, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraProcessKeyboard(camera, DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)  
        wireframeMode = true;

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)  
        wireframeMode = false;

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)  
    {
        camera->yaw = -17.0f;
        camera->pitch = -9.0f;
        vec3 newPos = {228.0f, 180.0f, 455.0f};
        glm_vec3_copy(newPos, camera->position);       
        cameraUpdate(camera); 
    }    

    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)  
    {
        camera->yaw = -1.0f;
        camera->pitch = -55.0f;
        vec3 newPos = {-311.0f, 1303.0f, 636.0f};
        glm_vec3_copy(newPos, camera->position);       
        cameraUpdate(camera); 
    }      
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
    int ret = snprintf(drawcallBuffer, sizeof(drawcallBuffer), "%d", drawcalls);

    strcat(windowTitleBuffer, drawcallBuffer);
    strcat(windowTitleBuffer, ")");
}