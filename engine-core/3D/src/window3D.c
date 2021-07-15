#include "window3D.h"

camera_t* camera = NULL;
bool wireframeMode = false;
bool generateNewTerrain = false;

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
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

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)  
    {
        camera->yaw = 33.0f;
        camera->pitch = -14.0f;
        vec3 newPos = {93.0f, 162.0f, 370.0f};
        glm_vec3_copy(newPos, camera->position);       
        cameraUpdate(camera); 
    }    

    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)  
    {
        camera->yaw = 0.0f;
        camera->pitch = -55.0f;
        vec3 newPos = {-331.0f, 1331.0f, 801.0f};
        glm_vec3_copy(newPos, camera->position);       
        cameraUpdate(camera); 
    }  

    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)  
        wireframeMode = true;

    if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)  
        wireframeMode = false;

    if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)  
        generateNewTerrain = true;
}

void window3DInit(char* title)
{
    windowInit(title);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LEQUAL));

    //Create camera
    camera = cameraCreate((vec3){-331.0f, 1331.0f, 801.0f}, 0.0f, -55.0f);
}

bool window3DIsRunning()
{
    return windowIsRunning();
}

void window3DPollEvents()
{
    glfwPollEvents();
    process_events();
}

void window3DPrepare()
{
    windowPrepare();
}

void window3DSwapBuffer()
{
    windowSwapBuffer();
}

void window3DCleanUp()
{
    windowCleanUp();
    cameraDestroy(camera);
}

void window3DCalcFrametime()
{
    windowCalcFrametime();
}

void window3DGetMousePos(double* x, double* y)
{
    windowGetMousePos(x, y);
}

void window3DUpdateTitle(int drawcalls)
{
    windowUpdateTitle(drawcalls);
}

void window3DPrepareDrawcallBuffer(int drawcalls)
{
    windowPrepareDrawcallBuffer(drawcalls);
}