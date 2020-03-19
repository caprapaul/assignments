#pragma once
#include "repository.h"

typedef struct
{
    Repository* repository;
}Service;

int ServiceCreate(Service** service, Repository* repository);
int ServiceDestroy(Service* service);

int ServiceAdd(Service* service, int locationCode, char* visibilityInArea, char* barricadeType, int barricadeSturdiness);
int ServiceRemove(Service* service, int locationCode);
int ServiceUpdate(Service* service, int locationCode, char* newVisibilityInArea, char* newBarricadeType, int newBarricadeSturdiness);
int ServiceGetCount(Service* service);
int ServiceGetAll(Service* service, Barricade* barricades);
int ServiceSearchBarricadeType(Service* service, char* barricadeType, Barricade* barricades, int* barricadesCount);
