#pragma once
#include "repository.h"

typedef struct
{
    Repository* repository;
} Service;

int ServiceCreate(Service** service, Repository* repository);
int ServiceDestroy(Service** service);

int ServiceAdd(Service* service, int locationCode, char* visibilityInArea, char* barricadeType, int barricadeSturdiness);
int ServiceRemove(Service* service, int locationCode);
int ServiceUpdate(Service* service, int locationCode, char* newVisibilityInArea, char* newBarricadeType, int newBarricadeSturdiness);
int ServiceGetCount(Service* service);
int ServiceGetAll(Service* service, Vector* barricades);
int ServiceSearchBarricadeType(Service* service, char* barricadeType, Vector* barricades);
int ServiceSearchMaximumBarricadeSturdiness(Service* service, int maximumBarricadeSturdiness, Vector* barricades);
