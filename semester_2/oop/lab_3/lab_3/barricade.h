#pragma once

#define BARRICADE_SUCCESS 0
#define BARRICADE_ERROR -1

typedef struct
{
    int locationCode;
    char visibilityInArea[10];
    char type[10];
    int sturdiness;
} Barricade;

int BarricadeCreate(Barricade** barricade, int locationCode, char* visibilityInArea, char* type, int sturdiness);
int BarricadeDestroy(Barricade** barricade);
int BarricadeCopy(Barricade** barricade, Barricade* other);

int BarricadeEqual(Barricade* barricade, Barricade* other);
int BarricadeEqualType(Barricade* barricade, Barricade* other);
int BarricadeCompareSturdiness(Barricade* barricade, Barricade* other);
