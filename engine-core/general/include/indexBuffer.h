#ifndef INDEXBUFFER
#define INDEXBUFFER

#include "../../vendor/include/glad.h"
#include "errorManager.h"

// --- Functions ---
unsigned int createIndexBuffer(const void* data, unsigned int size);
void deleteIndexBuffer(unsigned int iboID);
void bindIndexBuffer(unsigned int iboID);
void unbindIndexBuffer();

#endif