#pragma once
#include "barricade.h"
#include "vector.h"

#define REPOSITORY_SUCCESS 0
#define REPOSITORY_ERROR -1

typedef Barricade* TElement;
typedef int(*TElementComparator)(TElement element1, TElement element2);
typedef int(*TElementCopy)(TElement* element, TElement other);
typedef int(*TElementFunction)(TElement* element);

typedef struct 
{
    Vector* elements;
    TElementComparator equal;
    TElementCopy copy;
    int length;
} Repository;

int RepositoryCreate(Repository** repository, TElementComparator equal, TElementCopy copy);
int RepositoryDestroy(Repository** repository, TElementFunction elementDestroyer);

int RepositoryAdd(Repository* repository, TElement element);
int RepositoryRemove(Repository* repository, TElement element);
int RepositoryUpdate(Repository* repository, TElement oldElement, TElement newElement);
int RepositoryFind(Repository* repository, TElement element);
int RepositoryGetCount(Repository* repository);
int RepositoryGetAll(Repository* repository, Vector* elements);
int RepositorySearch(Repository* repository, TElement element, TElementComparator compare, Vector* elements);
