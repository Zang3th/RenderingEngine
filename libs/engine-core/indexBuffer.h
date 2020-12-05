#ifndef INDEXBUFFER
#define INDEXBUFFER

#include "../../vendor/loading/glad.h"
#include "errorManager.h"
#include <stdlib.h>

// --- Functions ---
unsigned int* createIndexBuffer(const void* data, unsigned int size);
void deleteIndexBuffer(unsigned int* iboID);
void bindIndexBuffer(const unsigned int* iboID);
void unbindIndexBuffer();

#endif