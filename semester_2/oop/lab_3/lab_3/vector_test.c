#include "vector_test.h"
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

void VectorCreate_ValidInput_Success()
{
    printf("Testing VectorCreate_ValidInput_Success... ");

    int resultCode = VECTOR_ERROR;
    Vector* usedVector = NULL;

    resultCode = VectorCreate(&usedVector);
    assert(resultCode == VECTOR_SUCCESS);

    printf("Success!\n");
}

void VectorPush_ValidInput_Success()
{
    printf("Testing VectorPush_ValidInput_Success... ");

    int resultCode = VECTOR_ERROR;
    Vector* usedVector = NULL;

    int pushVal = 10;

    resultCode = VectorPush(usedVector, &pushVal);
    assert(resultCode == VECTOR_SUCCESS);

    printf("Success!\n");
}

void VectorGetCount_EmptyVector_Zero()
{
    printf("Testing VectorGetCount_EmptyVector_Zero... ");

    int resultCode = VECTOR_ERROR;
    Vector* usedVector = NULL;

    assert(VectorGetCount(usedVector) == 0);

    printf("Success!\n");
}

void VectorGetCount_NonEmptyVector_One()
{
    printf("Testing VectorGetCount_EmptyVector_Zero... ");

    int resultCode = VECTOR_ERROR;
    Vector* usedVector = NULL;

    int pushVal = 10;

    VectorPush(usedVector, &pushVal);

    assert(VectorGetCount(usedVector) == 1);

    printf("Success!\n");
}


void TestVector()
{
    printf("Testing Vector... ");

    int resultCode = VECTOR_ERROR;
    Vector* usedVector = NULL;

    resultCode = VectorCreate(&usedVector);
    assert(resultCode == VECTOR_SUCCESS);

    int pushVal = 10;
    int* pushValP = &pushVal;

    resultCode = VectorPush(usedVector, &pushVal);
    assert(resultCode == VECTOR_SUCCESS);

    assert(VectorGetCount(usedVector) == 1);

    int insertVal = 20;
    int* insertValP = &insertVal;

    resultCode = VectorInsert(usedVector, 0, &insertVal);
    assert(resultCode == VECTOR_SUCCESS);

    resultCode = VectorRemove(usedVector, 0);
    assert(resultCode == VECTOR_SUCCESS);

    int* foundValP = NULL;
    resultCode = VectorGet(usedVector, 0, &foundValP);
    assert(resultCode == VECTOR_SUCCESS);

    assert(*foundValP == 10);

    resultCode = VectorClear(usedVector);
    assert(resultCode == VECTOR_SUCCESS);

    assert(VectorGetCount(usedVector) == 0);

    resultCode = VectorDestroy(&usedVector, NULL);
    assert(resultCode == VECTOR_SUCCESS);

    printf("Success!\n");
}