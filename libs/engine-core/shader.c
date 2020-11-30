#include "shader.h"

void printVector(float a, float b, float c, float d)
{
    vec2 v = {a, b};
    vec2 v2 = {c, d};
    vec2 v3;

    glm_vec2_add(v, v2, v3);
    log_info("x: %f, y: %f", v3[0], v3[1]); 
}