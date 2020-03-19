#include "barricade.h"
#include <stdlib.h>
#include <string.h>

int BarricadeCreate(Barricade** barricade, int locationCode, char* visibilityInArea, char* type, int sturdiness)
{
    *barricade = (Barricade*)malloc(sizeof(Barricade));

    if (*barricade == NULL)
    {
        return -1;
    }

    (*barricade)->locationCode = locationCode;
    strcpy((*barricade)->visibilityInArea, visibilityInArea);
    strcpy((*barricade)->type, type);
    (*barricade)->sturdiness = sturdiness;

    return 0;
}

int BarricadeCopy(Barricade ** barricade, Barricade * other)
{
    *barricade = (Barricade*)malloc(sizeof(Barricade));

    if (*barricade == NULL)
    {
        return -1;
    }

    (*barricade)->locationCode = other->locationCode;
    strcpy((*barricade)->visibilityInArea, other->visibilityInArea);
    strcpy((*barricade)->type, other->type);
    (*barricade)->sturdiness = other->sturdiness;

    return 0;
}

int BarricadeDestroy(Barricade** barricade)
{
    free(*barricade);
    *barricade = NULL;

    return 0;
}

int BarricadeCompare(Barricade* barricade, Barricade* other)
{
    if (barricade->locationCode == other->locationCode)
    {
        return 0;
    }
    else if (barricade->locationCode < other->locationCode)
    {
        return -1;
    }
    else if (barricade->locationCode > other->locationCode)
    {
        return 1;
    }

    return 0;
}

int BarricadeCompareType(Barricade* barricade, Barricade* other)
{
    if (strcmp(barricade->type, other->type) == 0)
    {
        return 1;
    }

    return 0;
}

int BarricadeCompareSturdiness(Barricade* barricade, Barricade* other)
{
    if (barricade->sturdiness == other->sturdiness)
    {
        return 0;
    }
    else if (barricade->sturdiness < other->sturdiness)
    {
        return -1;
    }
    else if (barricade->sturdiness > other->sturdiness)
    {
        return 1;
    }

    return 0;
}

