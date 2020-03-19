#include "service.h"
#include <stdlib.h>

int ServiceCreate(Service** service, Repository* repository)
{
    *service = (Service*)malloc(sizeof(Service));

    if (*service == NULL)
    {
        return -1;
    }

    (*service)->repository = repository;

    return 0;
}

int ServiceDestroy(Service* service)
{
    free(service);

    return 0;
}

int ServiceAdd(Service* service, int locationCode, char* visibilityInArea, char* barricadeType, int barricadeSturdiness)
{
    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, locationCode, visibilityInArea, barricadeType, barricadeSturdiness);

    return RepositoryAdd(service->repository, *barricade);
}

int ServiceRemove(Service* service, int locationCode)
{
    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, locationCode, "", "", 0);

    return RepositoryRemove(service->repository, *barricade);    
}

int ServiceUpdate(Service* service, int locationCode, char* newVisibilityInArea, char* newBarricadeType, int newBarricadeSturdiness)
{
    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, locationCode, newVisibilityInArea, newBarricadeType, newBarricadeSturdiness);

    return RepositoryUpdate(service->repository, *barricade, *barricade);
}

int ServiceGetCount(Service * service)
{
    return RepositoryGetCount(service->repository);
}

int ServiceGetAll(Service* service, Barricade* barricades)
{
    RepositoryGetAll(service->repository, barricades);

    return 0;
}

int ServiceSearchBarricadeType(Service* service, char* barricadeType, Barricade* barricades, int* barricadesCount)
{
    Barricade* barricade = NULL;
    BarricadeCreate(&barricade, 0, "", barricadeType, 0);

    return RepositorySearch(service->repository, BarricadeCompareType, *barricade, barricades, barricadesCount);
}
