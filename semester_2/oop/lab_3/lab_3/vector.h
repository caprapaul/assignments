#pragma once

#define VECTOR_SUCCESS 0
#define VECTOR_ERROR -1

typedef struct 
{
    void **items;
    int size;
    int count;
} Vector;

typedef int(*VectorItemFunction)(void** item);

int VectorCreate(Vector** vector);
int VectorDestroy(Vector** vector, VectorItemFunction itemDestroyer);

int VectorPush(Vector* vector, void* item);
int VectorPop(Vector* vector, void** item);
int VectorInsert(Vector* vector, int index, void* item);
int VectorRemove(Vector* vector, int index);
int VectorGet(Vector* vector, int index, void** item);
int VectorSet(Vector* vector, int index, void* item);

// Returns the number of element in vector or -1 in case of error or invalid parameters
int VectorGetCount(Vector* vector);
int VectorClear(Vector* vector);
