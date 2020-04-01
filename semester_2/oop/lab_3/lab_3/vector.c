#include "vector.h"
#include "stdlib.h"

#define INITIAL_SIZE 100

static int VectorEnlarge(Vector* vector)
{
    void* auxiliary = realloc(vector->items, sizeof(int) * vector->size * 2);

    if (auxiliary == NULL)
    {
        return VECTOR_ERROR;
    }

    vector->items = auxiliary;
    vector->size = 2 * vector->size;

    return VECTOR_SUCCESS;
}

static int VectorReduce(Vector* vector)
{
    int* auxiliary = (int*)realloc(vector->items, sizeof(int) * vector->size / 2);

    if (auxiliary == NULL)
    {
        return VECTOR_ERROR;
    }

    vector->items = auxiliary;
    vector->size = vector->size / 2;

    return VECTOR_SUCCESS;
}

int VectorCreate(Vector** vector)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    *vector = (Vector*)malloc(sizeof(Vector));

    if (*vector == NULL)
    {
        return VECTOR_ERROR;
    }

    memset((*vector), 0, sizeof(**vector));

    (*vector)->count = 0;
    (*vector)->size = INITIAL_SIZE;
    (*vector)->items = malloc(sizeof(void*) * INITIAL_SIZE);

    if ((*vector)->items == NULL)
    {
        free(*vector);
        return VECTOR_ERROR;
    }

    return VECTOR_SUCCESS;
}

int VectorDestroy(Vector** vector)
{
    Vector* temporary = *vector;

    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    free(temporary->items);
    free(temporary);

    *vector = NULL;

    return VECTOR_SUCCESS;
}

int VectorCopy(Vector** vector, Vector* other)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    *vector = (Vector*)malloc(sizeof(Vector));

    if (*vector == NULL)
    {
        return VECTOR_ERROR;
    }

    memset((*vector), 0, sizeof(**vector));

    (*vector)->count = 0;
    (*vector)->size = INITIAL_SIZE;
    (*vector)->items = malloc(sizeof(void*) * INITIAL_SIZE);

    if ((*vector)->items == NULL)
    {
        free(*vector);
        return VECTOR_ERROR;
    }

    for (int i = 0; i < VectorGetCount(other); i++)
    {
        void* currentElement = NULL;
        VectorGet(other, i, &currentElement);
        VectorPush(*vector, currentElement);
    }

    return VECTOR_SUCCESS;
}

int VectorPush(Vector* vector, void* item)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    if (vector->count >= vector->size)
    {
        if (VectorEnlarge(vector) != VECTOR_SUCCESS)
        {
            return VECTOR_ERROR;
        }
    }

    vector->items[vector->count] = item;
    vector->count++;

    return VECTOR_SUCCESS;
}

int VectorPop(Vector* vector, void** item)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    if (vector->count <= 0)
    {
        return VECTOR_ERROR;
    }

    *item = vector->items[vector->count - 1];
    vector->count--;

    return VECTOR_SUCCESS;
}

int VectorInsert(Vector* vector, int index, void* item)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    if (index > vector->count || index < 0)
    {
        return VECTOR_ERROR;
    }

    if (vector->count >= vector->size)
    {
        if (VectorEnlarge(vector) != 0)
        {
            return VECTOR_ERROR;
        }
    }

    for (int i = vector->count - 1; i >= index; i--)
    {
        vector->items[i + 1] = vector->items[i];
    }

    vector->items[index] = item;
    vector->count++;

    return VECTOR_SUCCESS;
}

int VectorRemove(Vector* vector, int index)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    if (index >= vector->count || index < 0)
    {
        return VECTOR_ERROR;
    }

    for (int i = index; i < vector->size - 1; i++)
    {
        vector->items[i] = vector->items[i + 1];
    }

    vector->count--;

    if (vector->count < vector->size / 2)
    {
        
    }

    return VECTOR_SUCCESS;
}

int VectorGet(Vector* vector, int index, void** item)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    if (index >= vector->count || index < 0)
    {
        return VECTOR_ERROR;
    }

    *item = vector->items[index];

    return VECTOR_SUCCESS;
}

int VectorSet(Vector* vector, int index, void* item)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    if (index >= vector->count || index < 0)
    {
        return VECTOR_ERROR;
    }

    vector->items[index] = item;

    return VECTOR_SUCCESS;
}

int VectorGetCount(Vector* vector)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    return vector->count;
}

int VectorClear(Vector* vector)
{
    if (vector == NULL)
    {
        return VECTOR_ERROR;
    }

    vector->count = 0;
    vector->size = INITIAL_SIZE;

    void** aux = realloc(vector->items, sizeof(void*) * vector->size);

    if (aux == NULL)
    {
        return VECTOR_ERROR;
    }

    memset(aux, 0, sizeof(*aux));

    vector->items = aux;

    return VECTOR_SUCCESS;
}
