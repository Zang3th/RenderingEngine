#ifndef RANDOM
#define RANDOM

#include <stdlib.h>

// --- Functions ---
float getPseudoRandom(float maxValue);
unsigned int getPseudoRandom_uint(unsigned int maxValue);
float getGoodRandom(float minValue, float maxValue);

#endif