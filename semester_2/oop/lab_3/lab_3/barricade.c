#include "barricade.h"
#include <stdlib.h>
#include <string.h>

int BarricadeCreate(Barricade** barricade, int locationCode, char* visibilityInArea, char* type, int sturdiness)
{
    *barricade = (Barricade*)malloc(sizeof(Barricade));

    if (*barricade == NULL)
    {
        return BARRICADE_ERROR;
    }

    (*barricade)->locationCode = locationCode;
    strcpy((*barricade)->visibilityInArea, visibilityInArea);
    strcpy((*barricade)->type, type);
    (*barricade)->sturdiness = sturdiness;

    return BARRICADE_SUCCESS;
}

int BarricadeCopy(Barricade** barricade, Barricade* other)
{
    *barricade = (Barricade*)malloc(sizeof(Barricade));

    if (*barricade == NULL)
    {
        return BARRICADE_ERROR;
    }

    (*barricade)->locationCode = other->locationCode;
    strcpy((*barricade)->visibilityInArea, other->visibilityInArea);
    strcpy((*barricade)->type, other->type);
    (*barricade)->sturdiness = other->sturdiness;

    return BARRICADE_SUCCESS;
}

int BarricadeDestroy(Barricade** barricade)
{
    free(*barricade);
    *barricade = NULL;

    return BARRICADE_SUCCESS;
}

int BarricadeEqual(Barricade* barricade, Barricade* other)
{
    if (barricade->locationCode == other->locationCode)
    {
        return 1;
    }

    return 0;
}

int BarricadeEqualType(Barricade* barricade, Barricade* other)
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

