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
int VectorDestroy(Vector** vector);
int VectorCopy(Vector** vector, Vector* other);

/// <summary>
/// Pushes an item at the end of the vector.
/// </summary>
int VectorPush(Vector* vector, void* item);

/// <summary>
/// Pops an item from the end of the vector.
/// </summary>
int VectorPop(Vector* vector, void** item);

/// <summary>
/// Inserts an item at a given index.
/// </summary>
int VectorInsert(Vector* vector, int index, void* item);

/// <summary>
/// Removes the item from a given index.
/// </summary>
int VectorRemove(Vector* vector, int index);

/// <summary>
/// Gets the item from a given index.
/// </summary>
int VectorGet(Vector* vector, int index, void** item);

/// <summary>
/// Sets the item at a given index.
/// </summary>
int VectorSet(Vector* vector, int index, void* item);

/// <summary>
// Returns the number of items in vector.
/// </summary>
int VectorGetCount(Vector* vector);

/// <summary>
/// Clears the items of the vector.
/// </summary>
int VectorClear(Vector* vector);
