#ifndef NOISE
#define NOISE

#include <math.h>
#include <stdlib.h>

// --- Variables ---
typedef struct{
    float roughness;
    unsigned int octaves;
    float divisor;
    float amplitude;
} noise_t;

// --- Functions ---
float random_float(float maxRange);
float getNoisePseudoRandom(float x, float z, float mul, float b);
float getNoisePerlin2D(float x, float z, noise_t* noiseStruct);

#endif