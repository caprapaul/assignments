#include "repository.h"
#include <stdlib.h>

int RepositoryCreate(Repository** repository, TElementComparator comparator)
{
    *repository = (Repository*)malloc(sizeof(Repository));

    if (*repository == NULL)
    {
        return -1;
    }

    (*repository)->length = 0;
    (*repository)->comparator = comparator;

    return 0;
}

int RepositoryDestroy(Repository* repository)
{
    free(repository);

    return 0;
}

int RepositoryAdd(Repository* repository, TElement element)
{
    if (RepositoryFind(repository, element) == 1)
    {
        return -1;
    }

    repository->elements[repository->length] = element;
    repository->length++;

    return 0;
}

int RepositoryRemove(Repository* repository, TElement element)
{
    int index = 0;
    int found = 0;

    while (index < repository->length && found == 0) 
    {
        TElement currentElement = repository->elements[index];

        if (repository->comparator(currentElement, element) == 0)
        {
            found = 1;
        }
        else 
        {
            index++;
        }
    }

    if (found != 1)
    {
        return -1;
    }

    repository->length--;

    for (int i = index; i < repository->length; i++)
    {
        repository->elements[i] = repository->elements[i + 1];
    }

    return 0;
}

int RepositoryUpdate(Repository* repository, TElement oldElement, TElement newElement)
{
    int index = 0;
    int found = 0;

    while (index < repository->length && found == 0)
    {
        TElement currentElement = repository->elements[index];

        if (repository->comparator(currentElement, oldElement) == 0)
        {
            repository->elements[index] = newElement;
            found = 1;
        }
        else
        {
            index++;
        }
    }

    if (found == 0)
    {
        return -1;
    }

    return 0;
}

int RepositoryFind(Repository * repository, TElement element)
{
    for (int i = 0; i < repository->length; i++)
    {
        TElement currentElement = repository->elements[i];

        if (repository->comparator(currentElement, element) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int RepositoryGetCount(Repository* repository)
{
    return repository->length;
}

int RepositoryGetAll(Repository* repository, TElement* elements)
{
    for (int i = 0; i < repository->length; i++)
    {
        elements[i] = repository->elements[i];
    }

    return 0;
}

int RepositorySearch(Repository* repository, TElementComparator compare, TElement element, TElement* elements, int* elementsCount)
{
    *elementsCount = 0;

    for (int i = 0; i < repository->length; i++)
    {
        TElement currentElement = repository->elements[i];

        if (compare(currentElement, element) == 1) 
        {
            elements[*elementsCount] = repository->elements[i];
            (*elementsCount)++;
        }
    }

    return 0;
}
