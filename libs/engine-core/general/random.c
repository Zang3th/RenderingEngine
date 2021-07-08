#include "random.h"

float getPseudoRandom(float maxValue)
{
    return (float)rand()/(float)(RAND_MAX/maxValue); 
}

unsigned int getPseudoRandom_uint(unsigned int maxValue)
{
    return rand()/(float)(RAND_MAX/maxValue); 
}

float getGoodRandom(float minValue, float maxValue)
{
    return 1.0f;
}