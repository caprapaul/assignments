#include "service.h"
#include <stdlib.h>

static int DestroyElements(Vector* vector)
{
    for (int i = 0; i < VectorGetCount(vector); i++)
    {
        TElement currentElement = NULL;
        VectorGet(vector, i, &currentElement);
        BarricadeDestroy(&currentElement);
    }
}

static int SaveRepositoryToUndo(Service* service)
{
    Vector* currentState = NULL;
    VectorCreate(&currentState);
    RepositoryGetAll(service->repository, currentState);
    VectorPush(service->undo, currentState);
}

static int SaveRepositoryToRedo(Service* service)
{
    Vector* currentState = NULL;
    VectorCreate(&currentState);
    RepositoryGetAll(service->repository, currentState);
    VectorPush(service->redo, currentState);
}

static int ClearUndo(Service *service)
{
    for (int i = 0; i < VectorGetCount(service->undo); i++)
    {
        Vector* currentState = NULL;
        VectorGet(service->undo, i, &currentState);
        DestroyElements(currentState);
        VectorDestroy(&currentState);
    }

    VectorClear(service->undo);
}

static int ClearRedo(Service *service)
{
    for (int i = 0; i < VectorGetCount(service->redo); i++)
    {
        Repository* currentState = NULL;
        VectorGet(service->redo, i, &currentState);
        DestroyElements(currentState);
        VectorDestroy(&currentState);
    }

    VectorClear(service->redo);
}

int ServiceCreate(Service** service, Repository* repository)
{
    *service = (Service*)malloc(sizeof(Service));

    if (*service == NULL)
    {
        return SERVICE_ERROR;
    }

    (*service)->repository = repository;
    VectorCreate(&((*service)->undo));
    VectorCreate(&((*service)->redo));

    return SERVICE_SUCCESS;
}

int ServiceDestroy(Service** service)
{
    ClearUndo(*service);
    ClearRedo(*service);
    VectorDestroy(&((*service)->undo));
    VectorDestroy(&((*service)->redo));

    free(*service);
    *service = NULL;

    return SERVICE_SUCCESS;
}

int ServiceAdd(Service* service, int locationCode, char* visibilityInArea, char* barricadeType, int barricadeSturdiness)
{
    SaveRepositoryToUndo(service);

    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, locationCode, visibilityInArea, barricadeType, barricadeSturdiness);

    return RepositoryAdd(service->repository, barricade);
}

int ServiceRemove(Service* service, int locationCode)
{
    SaveRepositoryToUndo(service);

    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, locationCode, "", "", 0);

    int resultCode = RepositoryRemove(service->repository, barricade);

    BarricadeDestroy(&barricade);

    return resultCode;
}

int ServiceUpdate(Service* service, int locationCode, char* newVisibilityInArea, char* newBarricadeType, int newBarricadeSturdiness)
{
    SaveRepositoryToUndo(service);

    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, locationCode, newVisibilityInArea, newBarricadeType, newBarricadeSturdiness);

    return RepositoryUpdate(service->repository, barricade, barricade);
}

int ServiceGetCount(Service * service)
{
    return RepositoryGetCount(service->repository);
}

int ServiceGetAll(Service* service, Vector* barricades)
{
    RepositoryGetAll(service->repository, barricades);

    return SERVICE_SUCCESS;
}

int ServiceSearchBarricadeType(Service* service, char* barricadeType, Vector* barricades)
{
    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, 0, "", barricadeType, 0);

    int resultCode = RepositorySearch(service->repository, barricade, BarricadeEqualType, barricades);

    BarricadeDestroy(&barricade);

    return resultCode;
}

static int BarricadeLowerOrEqualSturdiness(Barricade* barricade, Barricade* other)
{
    int compareResult = BarricadeCompareSturdiness(barricade, other);

    if (compareResult == -1 || compareResult == 0)
    {
        return 1;
    }

    return 0;
}

int ServiceSearchMaximumBarricadeSturdiness(Service* service, int maximumBarricadeSturdiness, Vector* barricades)
{
    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, 0, "", "", maximumBarricadeSturdiness);

    return RepositorySearch(service->repository, barricade, BarricadeLowerOrEqualSturdiness, barricades);
}

int ServiceUndo(Service* service)
{
    if (VectorGetCount(service->undo) <= 0)
    {
        return SERVICE_ERROR;
    }
    ClearRedo(service);
    SaveRepositoryToRedo(service);

    Vector* previousState = NULL;
    VectorPop(service->undo, &previousState);
    RepositoryClear(service->repository);
    RepositoryAddMultiple(service->repository, previousState);

    return SERVICE_SUCCESS;
}

int ServiceRedo(Service* service)
{
    if (VectorGetCount(service->redo) <= 0)
    {
        return SERVICE_ERROR;
    }

    SaveRepositoryToUndo(service);

    Vector* previousState = NULL;
    VectorPop(service->redo, &previousState);
    RepositoryClear(service->repository);
    RepositoryAddMultiple(service->repository, previousState);

    return SERVICE_SUCCESS;
}
