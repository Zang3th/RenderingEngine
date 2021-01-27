#ifndef NOISE
#define NOISE

#include <math.h>
#include <stdlib.h>

float getNoisePseudoRandom(float x, float z, float mul, float b);
float getNoisePerlin2D(float x, float z, float roughness, unsigned int octaves, float divisor);

#endif