#include "camera.h"

camera_t* cameraCreate(vec3 position, float yaw, float pitch)
{
    camera_t* cam = malloc(sizeof(camera_t));

    //Set position vector
    memcpy(&(cam->position[0]), &(position[0]), sizeof(float) * 3);

    //Set front vector
    vec3 front = {0.0f, 0.0f, -1.0f};
    memcpy(&(cam->front[0]), &front, sizeof(float) * 3);

    //Clear right vector
    memset(&(cam->right[0]), 0, sizeof(float) * 3);

    //Set up and world up vectors
    vec3 up = {0.0f, 1.0f, 0.0f};
    memcpy(&(cam->up[0]), &up, sizeof(float) * 3);
    memcpy(&(cam->worldUp[0]), &up, sizeof(float) * 3);

    //Set the rest
    cam->yaw = yaw;
    cam->pitch = pitch;
    cam->movementSpeed = 15.0f;
    cam->mouseSensitivity = 0.1f;

    return cam;
}

void cameraUpdate(camera_t* camera)
{
    //Calculate the new front vector
    vec3 newFront;
    newFront[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch)); //x
    newFront[1] = sin(glm_rad(camera->pitch));                             //y
    newFront[2] = sin(glm_rad(camera->yaw)) * sin(glm_rad(camera->pitch)); //z
    glm_normalize(newFront);
    memcpy(&(camera->front[0]), &newFront[0], sizeof(float) * 3);

    //Re-calculate the right vector
    vec3 newRight;
    glm_cross(camera->front, camera->worldUp, newRight);
    glm_normalize(newRight);
    memcpy(&(camera->right[0]), &newRight[0], sizeof(float) * 3);

    //Re-calculate the up vector
    vec3 newUp;
    glm_cross(camera->right, camera->front, newUp);
    glm_normalize(newUp);
    memcpy(&(camera->up[0]), &newUp[0], sizeof(float) * 3);
}   

void cameraProcessKeyboard(camera_t* camera, enum CAMERA_MOVEMENT direction, float dt)
{
    float velocity = camera->movementSpeed * dt;

    if(direction == FORWARD)
        glm_vec3_muladds(camera->front, velocity, camera->position);
    
    if(direction == BACKWARD)
        utility_vec3_mulsubs(camera->front, velocity, camera->position);

    if(direction == RIGHT)
        glm_vec3_muladds(camera->right, velocity, camera->position);

    if(direction == LEFT)
        utility_vec3_mulsubs(camera->right, velocity, camera->position);

    if(direction == UP)
        glm_vec3_muladds(camera->up, velocity, camera->position);

    if(direction == UP)
        utility_vec3_mulsubs(camera->up, velocity, camera->position);
}

void cameraProcessMouse(camera_t* camera, float xOffset, float yOffset)
{
    xOffset *= camera->mouseSensitivity;
    yOffset *= camera->mouseSensitivity;

    camera->yaw += xOffset;
    camera->pitch += yOffset;

    //Make sure that when pitch is out of bounds, screen doesn't get flipped
    if(camera->pitch > 89.0f)
        camera->pitch = 89.0f;

    if(camera->pitch < -89.0f)
        camera->pitch = -89.0f;  

    //Update Front, Right and Up Vectors using the updated Euler angles
	cameraUpdate(camera);       
}

void cameraGetViewMatrix(camera_t* camera, mat4 viewMatrix)
{
    vec3 center;
    glm_vec3_add(camera->position, camera->front, center);    
    glm_lookat(camera->position, center, camera->up, viewMatrix);    
}

void cameraDestroy(camera_t* camera)
{
    free(camera);
}