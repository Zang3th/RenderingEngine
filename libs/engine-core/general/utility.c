#include "utility.h"

void utility_vec3_mulsubs(vec3 a, float s, vec3 dest) 
{
  dest[0] -= a[0] * s;
  dest[1] -= a[1] * s;
  dest[2] -= a[2] * s;
}

void utility_print_mat4(mat4 matrix)
{
  log_info("(%6.2f | %6.2f | %6.2f | %6.2f)", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
  log_info("(%6.2f | %6.2f | %6.2f | %6.2f)", matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
  log_info("(%6.2f | %6.2f | %6.2f | %6.2f)", matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
  log_info("(%6.2f | %6.2f | %6.2f | %6.2f)", matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
}

void utility_print_vec3(vec3 vector)
{
  log_info("(%6.2f | %6.2f | %6.2f)", vector[0], vector[1], vector[2]);
}