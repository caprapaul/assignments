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

int BarricadeDestroy(Barricade* barricade)
{
    free(barricade);

    return 0;
}

int BarricadeCompare(Barricade barricade1, Barricade barricade2)
{
    if (barricade1.locationCode == barricade2.locationCode)
    {
        return 0;
    }
    else if (barricade1.locationCode < barricade2.locationCode)
    {
        return -1;
    }
    else if (barricade1.locationCode > barricade2.locationCode)
    {
        return 1;
    }

    return 0;
}

int BarricadeCompareType(Barricade barricade1, Barricade barricade2)
{
    if (strcmp(barricade1.type, barricade2.type) == 0)
    {
        return 1;
    }

    return 0;
}
