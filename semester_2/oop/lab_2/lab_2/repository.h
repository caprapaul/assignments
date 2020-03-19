#pragma once
#include "barricade.h"

#define MAX_SIZE 100
#define SUCCESS_CODE 0

typedef Barricade TElement;
typedef int(*TElementComparator)(TElement element1, TElement element2);

typedef struct 
{
    TElement elements[MAX_SIZE];
    TElementComparator comparator;
    int length;
} Repository;

int RepositoryCreate(Repository** repository, TElementComparator comparator);
int RepositoryDestroy(Repository* repository);

int RepositoryAdd(Repository* repository, TElement element);
int RepositoryRemove(Repository* repository, TElement element);
int RepositoryUpdate(Repository* repository, TElement oldElement, TElement newElement);
int RepositoryFind(Repository* repository, TElement element);
int RepositoryGetCount(Repository* repository);
int RepositoryGetAll(Repository* repository, TElement* elements);
int RepositorySearch(Repository* repository, TElementComparator compare, TElement element, TElement* elements, int* elementsCount);
