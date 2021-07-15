#ifndef UTILITY
#define UTILITY

#include <cglm/cglm.h>
#include "../../vendor/include/log.h"

//My implementation of mulsubs cause cglm doesn't have one
void utility_vec3_mulsubs(vec3 a, float s, vec3 dest);
void utility_print_mat4(mat4 matrix);
void utility_print_vec3(vec3 vector);

#endif