#pragma once

typedef struct
{
    int locationCode;
    char visibilityInArea[10];
    char type[10];
    int sturdiness;
} Barricade;

int BarricadeCreate(Barricade** barricade, int locationCode, char* visibilityInArea, char* type, int sturdiness);
int BarricadeDestroy(Barricade* barricade);

int BarricadeCompare(Barricade barricade1, Barricade barricade2);
int BarricadeCompareType(Barricade barricade1, Barricade barricade2);
