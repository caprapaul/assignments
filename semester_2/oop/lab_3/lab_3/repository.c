#include "repository.h"
#include <stdlib.h>

int RepositoryCreate(Repository** repository, TElementComparator equal, TElementCopy copy)
{
    *repository = (Repository*)malloc(sizeof(Repository));

    if (*repository == NULL)
    {
        return REPOSITORY_ERROR;
    }

    (*repository)->length = 0;
    (*repository)->copy = copy;
    (*repository)->equal = equal;

    VectorCreate(&((*repository)->elements));

    return REPOSITORY_SUCCESS;
}

int RepositoryDestroy(Repository** repository, TElementFunction elementDestroyer)
{
    VectorDestroy(&((*repository)->elements), elementDestroyer);

    free(*repository);
    *repository = NULL;

    return REPOSITORY_SUCCESS;
}

int RepositoryAdd(Repository* repository, TElement element)
{
    if (RepositoryFind(repository, element) == 1)
    {
        return REPOSITORY_ERROR;
    }

    VectorPush(repository->elements, element);
    repository->length++;

    return REPOSITORY_SUCCESS;
}

int RepositoryRemove(Repository* repository, TElement element)
{
    int index = 0;
    int found = 0;

    while (index < repository->length && found == 0) 
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, index, &currentElement);

        if (repository->equal(currentElement, element) == 0)
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
        return REPOSITORY_ERROR;
    }

    repository->length--;

    for (int i = index; i < repository->length; i++)
    {
        repository->elements[i] = repository->elements[i + 1];
    }

    return REPOSITORY_SUCCESS;
}

int RepositoryUpdate(Repository* repository, TElement oldElement, TElement newElement)
{
    int index = 0;
    int found = 0;

    while (index < repository->length && found == 0)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, index, &currentElement);

        if (repository->equal(currentElement, oldElement) == 0)
        {
            VectorSet(repository->elements, index, newElement);
            found = 1;
        }
        else
        {
            index++;
        }
    }

    if (found == 0)
    {
        return REPOSITORY_ERROR;
    }

    return REPOSITORY_SUCCESS;
}

int RepositoryFind(Repository* repository, TElement element)
{
    for (int i = 0; i < repository->length; i++)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, i, &currentElement);

        if (repository->equal(currentElement, element) == 0)
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

int RepositoryGetAll(Repository* repository, Vector* elements)
{
    for (int i = 0; i < repository->length; i++)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, i, &currentElement);

        TElement currentElementCopy = NULL;
        repository->copy(&currentElementCopy, currentElement);

        VectorPush(elements, currentElementCopy);
    }

    return REPOSITORY_SUCCESS;
}

int RepositorySearch(Repository* repository, TElement element, TElementComparator compare, Vector* elements)
{
    for (int i = 0; i < repository->length; i++)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, i, &currentElement);

        TElement currentElementCopy = NULL;
        repository->copy(&currentElementCopy, currentElement);

        if (compare(currentElement, element) == 1)
        {
            VectorPush(elements, currentElementCopy);
        }
    }

    return REPOSITORY_SUCCESS;
}
