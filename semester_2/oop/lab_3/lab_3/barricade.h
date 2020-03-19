#pragma once

typedef struct
{
    int locationCode;
    char visibilityInArea[10];
    char type[10];
    int sturdiness;
} Barricade;

int BarricadeCreate(Barricade** barricade, int locationCode, char* visibilityInArea, char* type, int sturdiness);
int BarricadeCopy(Barricade** barricade, Barricade* other);
int BarricadeDestroy(Barricade** barricade);

int BarricadeCompare(Barricade* barricade, Barricade* other);
int BarricadeCompareType(Barricade* barricade, Barricade* other);
int BarricadeCompareSturdiness(Barricade* barricade, Barricade* other);
