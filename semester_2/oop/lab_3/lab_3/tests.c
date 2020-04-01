#include "tests.h"
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

void VectorCreate_ValidInput_Success()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    resultCode = VectorCreate(&vector);

    assert(resultCode == VECTOR_SUCCESS);

    VectorDestroy(&vector);
}

void VectorDestroy_ValidInput_Success()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);
    resultCode = VectorDestroy(&vector);

    assert(resultCode == VECTOR_SUCCESS);
}

void VectorGet_IndexOutOfRange_Error()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int* getItem = NULL;
    resultCode = VectorGet(vector, 1, &getItem);

    assert(resultCode == VECTOR_ERROR);

    VectorDestroy(&vector);
}

void VectorPush_ValidInput_PushedToVector()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int pushValue = 10;
    resultCode = VectorPush(vector, &pushValue);

    assert(resultCode == VECTOR_SUCCESS);
    assert(VectorGetCount(vector) == 1);

    VectorDestroy(&vector);
}

void VectorPop_EmptyVector_Error()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int* popItem = NULL;
    resultCode = VectorPop(vector, &popItem);

    assert(resultCode == VECTOR_ERROR);

    VectorDestroy(&vector);
}

void VectorPop_NonEmptyVector_PoppedFromVector()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int pushValue = 10;
    VectorPush(vector, &pushValue);

    int* popItem = NULL;
    resultCode = VectorPop(vector, &popItem);

    assert(resultCode == VECTOR_SUCCESS );
    assert(VectorGetCount(vector) == 0);
    assert(*popItem == pushValue);

    VectorDestroy(&vector);
}

void VectorInsert_ValidInput_InsertedToVector()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int insertValue1 = 20;
    VectorPush(vector, &insertValue1);

    int insertValue0 = 10;
    resultCode = VectorInsert(vector, 0, &insertValue0);

    assert(resultCode == VECTOR_SUCCESS);

    int* getItem = NULL;
    VectorGet(vector, 0, &getItem);

    assert(*getItem == insertValue0);

    VectorDestroy(&vector);
}

void VectorInsert_IndexOutOfRange_Error()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int insertValue = 10;
    resultCode = VectorInsert(vector, 1, &insertValue);

    assert(resultCode == VECTOR_ERROR);

    VectorDestroy(&vector);
}

void VectorRemove_ValidInput_RemovedFromVector()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int insertValue = 10;
    VectorPush(vector, &insertValue);

    resultCode = VectorRemove(vector, 0);

    assert(resultCode == VECTOR_SUCCESS);
    assert(VectorGetCount(vector) == 0);

    VectorDestroy(&vector);
}

void VectorRemove_IndexOutOfRange_Error()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    resultCode = VectorRemove(vector, 0);

    assert(resultCode == VECTOR_ERROR);

    VectorDestroy(&vector);
}

void VectorSet_ValidInput_ModifiedItem()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int insertValue = 10;
    VectorPush(vector, &insertValue);

    int setValue = 20;
    resultCode = VectorSet(vector, 0, &setValue);

    int* getItem = NULL;
    VectorGet(vector, 0, &getItem);

    assert(resultCode == VECTOR_SUCCESS);
    assert(*getItem == setValue);

    VectorDestroy(&vector);
}

void VectorSet_IndexOutOfRange_Error()
{
    int resultCode = VECTOR_ERROR;
    Vector* vector = NULL;

    VectorCreate(&vector);

    int setValue = 10;
    resultCode = VectorSet(vector, 0, &setValue);

    assert(resultCode == VECTOR_ERROR);

    VectorDestroy(&vector);
}

void TestVector()
{
    VectorCreate_ValidInput_Success();
    VectorDestroy_ValidInput_Success();
    VectorGet_IndexOutOfRange_Error();
    VectorPush_ValidInput_PushedToVector();
    VectorPop_EmptyVector_Error();
    VectorPop_NonEmptyVector_PoppedFromVector();
    VectorInsert_ValidInput_InsertedToVector();
    VectorInsert_IndexOutOfRange_Error();
    VectorRemove_ValidInput_RemovedFromVector();
    VectorRemove_IndexOutOfRange_Error();
    VectorSet_ValidInput_ModifiedItem();
    VectorSet_IndexOutOfRange_Error();
}

void BarricadeCreate_ValidInput_Success()
{
    int resultCode = BARRICADE_ERROR;
    Barricade* barricade = NULL;

    resultCode = BarricadeCreate(&barricade, 10, "", "", 10);

    assert(resultCode == BARRICADE_SUCCESS);

    BarricadeDestroy(&barricade);
}

void BarricadeDestroy_ValidInput_Success()
{
    int resultCode = BARRICADE_ERROR;
    Barricade* barricade = NULL;

    BarricadeCreate(&barricade, 10, "", "", 10);

    resultCode = BarricadeDestroy(&barricade);

    assert(resultCode == BARRICADE_SUCCESS);
}

void BarricadeEqual_SameLocationCode_ReturnsOne()
{
    int resultCode = BARRICADE_ERROR;
    Barricade* barricade1 = NULL;

    BarricadeCreate(&barricade1, 10, "", "", 10);

    Barricade* barricade2 = NULL;
    BarricadeCreate(&barricade2, 10, "", "", 20);

    assert(BarricadeEqual(barricade1, barricade2) == 1);

    BarricadeDestroy(&barricade2);
    BarricadeDestroy(&barricade1);
}

void BarricadeEqual_DifferentLocationCode_ReturnsZero()
{
    int resultCode = BARRICADE_ERROR;
    Barricade* barricade1 = NULL;

    BarricadeCreate(&barricade1, 10, "", "", 10);

    Barricade* barricade2 = NULL;
    BarricadeCreate(&barricade2, 20, "", "", 20);

    assert(BarricadeEqual(barricade1, barricade2) == 0);

    BarricadeDestroy(&barricade2);
    BarricadeDestroy(&barricade1);
}

void BarricadeCopy_ValidInput_CopiedBarricade()
{
    int resultCode = BARRICADE_ERROR;
    Barricade* barricade = NULL;

    BarricadeCreate(&barricade, 10, "", "", 10);

    Barricade* barricadeCopy = NULL;
    resultCode = BarricadeCopy(&barricadeCopy, barricade);

    assert(resultCode == BARRICADE_SUCCESS);
    assert(BarricadeEqual(barricade, barricade) == 1);

    BarricadeDestroy(&barricadeCopy);
    BarricadeDestroy(&barricade);
}

void BarricadeCompareType_SameType_ReturnsOne()
{
    int resultCode = BARRICADE_ERROR;
    Barricade* barricade1 = NULL;

    BarricadeCreate(&barricade1, 10, "", "test", 10);

    Barricade* barricade2 = NULL;
    BarricadeCreate(&barricade2, 20, "", "test", 20);

    assert(BarricadeEqualType(barricade1, barricade2) == 1);

    BarricadeDestroy(&barricade2);
    BarricadeDestroy(&barricade1);
}

void BarricadeCompareType_DifferentType_ReturnsZero()
{
    int resultCode = BARRICADE_ERROR;
    Barricade* barricade1 = NULL;

    BarricadeCreate(&barricade1, 10, "", "test1", 10);

    Barricade* barricade2 = NULL;
    BarricadeCreate(&barricade2, 20, "", "test2", 20);

    assert(BarricadeEqualType(barricade1, barricade2) == 0);

    BarricadeDestroy(&barricade2);
    BarricadeDestroy(&barricade1);
}

void TestBarricade()
{
    BarricadeCreate_ValidInput_Success();
    BarricadeDestroy_ValidInput_Success();
    BarricadeEqual_SameLocationCode_ReturnsOne();
    BarricadeEqual_DifferentLocationCode_ReturnsZero();
    BarricadeCopy_ValidInput_CopiedBarricade();
    BarricadeCompareType_SameType_ReturnsOne();
    BarricadeCompareType_DifferentType_ReturnsZero();
}

void RepositoryCreate_ValidInput_Success()
{
    int resultCode = REPOSITORY_ERROR;
    Repository* repository = NULL;

    resultCode = RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    assert(resultCode == REPOSITORY_SUCCESS);

    RepositoryDestroy(&repository);
}

void RepositoryDestroy_ValidInput_Success()
{
    int resultCode = REPOSITORY_ERROR;
    Repository* repository = NULL;

    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    resultCode = RepositoryDestroy(&repository);

    assert(resultCode == REPOSITORY_SUCCESS);
}

void RepositoryAdd_ValidInput_AddedElement()
{
    int resultCode = REPOSITORY_ERROR;
    Repository* repository = NULL;

    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Barricade* addElement = NULL;
    BarricadeCreate(&addElement, 10, "", "", 10);
    resultCode = RepositoryAdd(repository, addElement);

    assert(resultCode == REPOSITORY_SUCCESS);
    assert(RepositoryFind(repository, addElement) == 1);

    RepositoryDestroy(&repository);
}

void RepositoryAdd_DuplicateElement_Error()
{
    int resultCode = REPOSITORY_ERROR;
    Repository* repository = NULL;

    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Barricade* addElement = NULL;
    BarricadeCreate(&addElement, 10, "", "", 10);
    RepositoryAdd(repository, addElement);

    resultCode = RepositoryAdd(repository, addElement);

    assert(resultCode == REPOSITORY_ERROR);

    RepositoryDestroy(&repository);
}

void RepositoryRemove_ValidInput_RemovedElement()
{
    int resultCode = REPOSITORY_ERROR;
    Repository* repository = NULL;

    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Barricade* addElement = NULL;
    BarricadeCreate(&addElement, 10, "", "", 10);
    RepositoryAdd(repository, addElement);

    resultCode = RepositoryRemove(repository, addElement);

    assert(resultCode == REPOSITORY_SUCCESS);
    assert(RepositoryFind(repository, addElement) == 0);

    RepositoryDestroy(&repository);
}

void RepositoryUpdate_ValidInput_UpdatedElement()
{
    int resultCode = REPOSITORY_ERROR;
    Repository* repository = NULL;

    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Barricade* addElement = NULL;
    BarricadeCreate(&addElement, 10, "", "", 10);
    RepositoryAdd(repository, addElement);

    Barricade* updateElement = NULL;
    BarricadeCreate(&updateElement, 10, "", "", 20);
    resultCode = RepositoryUpdate(repository, addElement, updateElement);

    assert(resultCode == REPOSITORY_SUCCESS);
    assert(RepositoryFind(repository, updateElement) == 1);

    RepositoryDestroy(&repository);
}

void RepositorySearch_ValidInput_FoundElement()
{
    int resultCode = REPOSITORY_ERROR;
    Repository* repository = NULL;

    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Barricade* addElement = NULL;
    BarricadeCreate(&addElement, 10, "", "", 10);
    RepositoryAdd(repository, addElement);

    Vector* foundElements = NULL;
    VectorCreate(&foundElements);
    resultCode = RepositorySearch(repository, addElement, BarricadeEqualType, foundElements);

    Barricade* foundElement = NULL;
    VectorGet(foundElements, 0, &foundElement);

    assert(resultCode == REPOSITORY_SUCCESS);
    assert(BarricadeEqual(foundElement, addElement));

    BarricadeDestroy(&foundElement);
    VectorDestroy(&foundElements);
    RepositoryDestroy(&repository);
}

void TestRepository()
{
    RepositoryCreate_ValidInput_Success();
    RepositoryDestroy_ValidInput_Success();
    RepositoryAdd_ValidInput_AddedElement();
    RepositoryAdd_DuplicateElement_Error();
    RepositoryRemove_ValidInput_RemovedElement();
    RepositoryUpdate_ValidInput_UpdatedElement();
    RepositorySearch_ValidInput_FoundElement();
}

void ServiceCreate_ValidInput_Success()
{
    int resultCode = SERVICE_ERROR;
    Repository* repository = NULL;
    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Service* service = NULL;
    resultCode = ServiceCreate(&service, repository);

    assert(resultCode == SERVICE_SUCCESS);

    ServiceDestroy(&service);
    RepositoryDestroy(&repository);
}

void ServiceDestroy_ValidInput_Success()
{
    int resultCode = SERVICE_ERROR;
    Repository* repository = NULL;
    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Service* service = NULL;
    ServiceCreate(&service, repository);

    resultCode = ServiceDestroy(&service);

    assert(resultCode == SERVICE_SUCCESS);

    RepositoryDestroy(&repository);
}

void ServiceAdd_ValidInput_AddedToRepository()
{
    int resultCode = SERVICE_ERROR;
    Repository* repository = NULL;
    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Service* service = NULL;
    ServiceCreate(&service, repository);

    resultCode = ServiceAdd(service, 10, "", "", 10);

    Vector* elements = NULL;
    VectorCreate(&elements);
    ServiceGetAll(service, elements);

    Barricade* getElement = NULL;
    VectorGet(elements, 0, &getElement);

    Barricade* addedElement = NULL;
    BarricadeCreate(&addedElement, 10, "", "", 10);

    assert(resultCode == SERVICE_SUCCESS);
    assert(BarricadeEqual(getElement, addedElement) == 1);

    BarricadeDestroy(&addedElement);
    BarricadeDestroy(&getElement);
    VectorDestroy(&elements);
    ServiceDestroy(&service);
    RepositoryDestroy(&repository);
}

void ServiceRemove_ValidInput_RemovedFromRepository()
{
    int resultCode = SERVICE_ERROR;
    Repository* repository = NULL;
    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Service* service = NULL;
    ServiceCreate(&service, repository);

    ServiceAdd(service, 10, "", "", 10);
    resultCode = ServiceRemove(service, 10);

    assert(resultCode == SERVICE_SUCCESS);
    assert(ServiceGetCount(service) == 0);

    ServiceDestroy(&service);
    RepositoryDestroy(&repository);
}

void ServiceSearchBarricadeType_ValidInput_FoundBarricade()
{
    int resultCode = SERVICE_ERROR;
    Repository* repository = NULL;
    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Service* service = NULL;
    ServiceCreate(&service, repository);

    ServiceAdd(service, 10, "", "test1", 10);
    ServiceAdd(service, 20, "", "test2", 10);

    Vector* foundElements = NULL;
    VectorCreate(&foundElements);
    resultCode = ServiceSearchBarricadeType(service, "test2", foundElements);

    Barricade* getElement = NULL;
    VectorGet(foundElements, 0, &getElement);

    Barricade* addedElement2 = NULL;
    BarricadeCreate(&addedElement2, 20, "", "test2", 10);

    assert(resultCode == SERVICE_SUCCESS);
    assert(VectorGetCount(foundElements) == 1);
    assert(BarricadeEqual(getElement, addedElement2) == 1);

    BarricadeDestroy(&addedElement2);
    BarricadeDestroy(&getElement);
    VectorDestroy(&foundElements);
    ServiceDestroy(&service);
    RepositoryDestroy(&repository);
}

void ServiceUndo_ExistingOperation_UndidOperation()
{
    int resultCode = SERVICE_ERROR;
    Repository* repository = NULL;
    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Service* service = NULL;
    ServiceCreate(&service, repository);

    ServiceAdd(service, 10, "", "test1", 10);

    resultCode = ServiceUndo(service);

    assert(resultCode == SERVICE_SUCCESS);
    assert(ServiceGetCount(service) == 0);

    ServiceDestroy(&service);
    RepositoryDestroy(&repository);
}

void ServiceRedo_ExistingOperation_RedidOperation()
{
    int resultCode = SERVICE_ERROR;
    Repository* repository = NULL;
    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);

    Service* service = NULL;
    ServiceCreate(&service, repository);

    ServiceAdd(service, 10, "", "test1", 10);

    ServiceUndo(service);
    resultCode = ServiceRedo(service);

    assert(resultCode == SERVICE_SUCCESS);
    assert(ServiceGetCount(service) == 1);

    ServiceDestroy(&service);
    RepositoryDestroy(&repository);
}

void TestService()
{
    ServiceCreate_ValidInput_Success();
    ServiceDestroy_ValidInput_Success();
    ServiceAdd_ValidInput_AddedToRepository();
    ServiceRemove_ValidInput_RemovedFromRepository();
    ServiceSearchBarricadeType_ValidInput_FoundBarricade();
    ServiceUndo_ExistingOperation_UndidOperation();
    ServiceRedo_ExistingOperation_RedidOperation();
}
