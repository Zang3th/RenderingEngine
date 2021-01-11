#include "utility.h"

void utility_vec3_mulsubs(vec3 a, float s, vec3 dest) 
{
  dest[0] += a[0] * s;
  dest[1] += a[1] * s;
  dest[2] += a[2] * s;
}