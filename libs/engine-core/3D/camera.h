#ifndef CAMERA
#define CAMERA

#include <cglm/cglm.h>
#include <cglm/vec3.h>
#include <cglm/mat4.h>
#include <string.h>
#include "../general/utility.h"

enum CAMERA_MOVEMENT
{
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

typedef struct
{
    //Camera attributes
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    //Euler angles
    float yaw;
    float pitch;

    //Camera options
    float movementSpeed;
    float mouseSensitivity;
} camera_t;

camera_t* cameraCreate(vec3 position, float yaw, float pitch);
void cameraUpdate(camera_t* camera);
void cameraProcessKeyboard(camera_t* camera, enum CAMERA_MOVEMENT direction, float dt);
void cameraProcessMouse(camera_t* camera, float xOffset, float yOffset);
void cameraGetViewMatrix(camera_t* camera, mat4 viewMatrix);
void cameraDestroy(camera_t* camera);

#endif