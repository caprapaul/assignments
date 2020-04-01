#include "repository.h"
#include <stdlib.h>

static int DestroyElements(Repository* repository)
{
    for (int i = 0; i < VectorGetCount(repository->elements); i++)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, i, &currentElement);

        repository->elementDestroyer(&currentElement);
    }
}

int RepositoryCreate(Repository** repository, TElementComparator elementEqual, TElementCopy elementCopy, TElementFunction elementDestroyer)
{
    *repository = (Repository*)malloc(sizeof(Repository));

    if (*repository == NULL)
    {
        return REPOSITORY_ERROR;
    }

    (*repository)->elementCopy = elementCopy;
    (*repository)->elementEqual = elementEqual;
    (*repository)->elementDestroyer = elementDestroyer;

    VectorCreate(&((*repository)->elements));

    return REPOSITORY_SUCCESS;
}

int RepositoryDestroy(Repository** repository)
{
    DestroyElements(*repository);

    VectorDestroy(&((*repository)->elements));

    free(*repository);
    *repository = NULL;

    return REPOSITORY_SUCCESS;
}

int RepositoryCopy(Repository** repository, Repository* other)
{
    *repository = (Repository*)malloc(sizeof(Repository));

    if (*repository == NULL)
    {
        return REPOSITORY_ERROR;
    }

    (*repository)->elementCopy = other->elementCopy;
    (*repository)->elementEqual = other->elementEqual;
    (*repository)->elementDestroyer = other->elementDestroyer;

    VectorCreate(&((*repository)->elements));

    for (int i = 0; i < VectorGetCount(other->elements); i++)
    {
        TElement currentElement = NULL;
        VectorGet(other->elements, i, &currentElement);

        TElement currentElementCopy = NULL;
        other->elementCopy(&currentElementCopy, currentElement);

        VectorPush((*repository)->elements, currentElementCopy);
    }


    return REPOSITORY_SUCCESS;
}

int RepositoryAdd(Repository* repository, TElement element)
{
    if (RepositoryFind(repository, element) == 1)
    {
        return REPOSITORY_ERROR;
    }

    VectorPush(repository->elements, element);

    return REPOSITORY_SUCCESS;
}

int RepositoryAddMultiple(Repository* repository, Vector* elements)
{
    for (int i = 0; i < VectorGetCount(elements); i++)
    {
        TElement currentElement = NULL;
        VectorGet(elements, i, &currentElement);

        if (RepositoryFind(repository, currentElement) == 1)
        {
            continue;
        }

        VectorPush(repository->elements, currentElement);
    }

    return REPOSITORY_SUCCESS;
}

int RepositoryRemove(Repository* repository, TElement element)
{
    int index = 0;
    int found = 0;

    while (index < VectorGetCount(repository->elements) && found == 0)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, index, &currentElement);

        if (repository->elementEqual(currentElement, element) == 1)
        {
            repository->elementDestroyer(&currentElement);
            found = 1;
            break;
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

    VectorRemove(repository->elements, index);

    return REPOSITORY_SUCCESS;
}

int RepositoryUpdate(Repository* repository, TElement oldElement, TElement newElement)
{
    int index = 0;
    int found = 0;

    while (index < VectorGetCount(repository->elements) && found == 0)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, index, &currentElement);

        if (repository->elementEqual(currentElement, oldElement) == 1)
        {
            repository->elementDestroyer(&currentElement);
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
    for (int i = 0; i < VectorGetCount(repository->elements); i++)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, i, &currentElement);

        if (repository->elementEqual(currentElement, element) == 1)
        {
            return 1;
        }
    }

    return 0;
}

int RepositoryGetCount(Repository* repository)
{
    return VectorGetCount(repository->elements);
}

int RepositoryGetAll(Repository* repository, Vector* elements)
{
    for (int i = 0; i < VectorGetCount(repository->elements); i++)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, i, &currentElement);

        TElement currentElementCopy = NULL;
        repository->elementCopy(&currentElementCopy, currentElement);

        VectorPush(elements, currentElementCopy);
    }

    return REPOSITORY_SUCCESS;
}

int RepositorySearch(Repository* repository, TElement element, TElementComparator compare, Vector* elements)
{
    for (int i = 0; i < VectorGetCount(repository->elements); i++)
    {
        TElement currentElement = NULL;
        VectorGet(repository->elements, i, &currentElement);

        TElement currentElementCopy = NULL;
        repository->elementCopy(&currentElementCopy, currentElement);

        if (compare(currentElement, element) == 1)
        {
            VectorPush(elements, currentElementCopy);
        }
    }

    return REPOSITORY_SUCCESS;
}

int RepositoryClear(Repository* repository)
{
    return VectorClear(repository->elements);
}
