#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int UICreate(UI** ui, Service* service)
{
    *ui = (UI*)malloc(sizeof(UI));

    if (*ui == NULL)
    {
        return -1;
    }

    (*ui)->service = service;

    return 0;
}

int UIDestroy(UI* ui)
{
    free(ui);

    return 0;
}

static void add(UI* ui, char arguments[][10], int argumentsCount)
{
    int locationCode = atoi(arguments[1]);
    char* visibilityInArea = arguments[2];
    char* barricadeType = arguments[3];
    int barricadeSturdiness = atoi(arguments[4]);

    int addResultCode = ServiceAdd(ui->service, locationCode, visibilityInArea, barricadeType, barricadeSturdiness);

    if (addResultCode != SUCCESS_CODE)
    {
        printf("No!\n");
    }
}

static void update(UI* ui, char arguments[][10], int argumentsCount)
{
    int locationCode = atoi(arguments[1]);
    char* newVisibilityInArea = arguments[2];
    char* newBarricadeType = arguments[3];
    int newBarricadeSturdiness = atoi(arguments[4]);

    int updateResultCode = ServiceUpdate(ui->service, locationCode, newVisibilityInArea, newBarricadeType, newBarricadeSturdiness);

    if (updateResultCode != SUCCESS_CODE)
    {
        printf("No!\n");
    }
}

static void delete(UI* ui, char arguments[][10], int argumentsCount)
{
    int locationCode = atoi(arguments[1]);
    int removeResultCode = ServiceRemove(ui->service, locationCode);

    if (removeResultCode != SUCCESS_CODE)
    {
        printf("No!\n");
    }
}

static void list(UI* ui, char arguments[][10], int argumentsCount)
{
    Barricade barricades[100];
    int barricadesCount = 0;

    if (argumentsCount == 1)
    {
        barricadesCount = ServiceGetCount(ui->service);
        ServiceGetAll(ui->service, barricades);
    }
    else if (argumentsCount == 2)
    {
        char* barricadeType = arguments[1];
        ServiceSearchBarricadeType(ui->service, barricadeType, barricades, &barricadesCount);
    }

    for (int i = 0; i < barricadesCount; i++)
    {
        Barricade current = barricades[i];
        printf("%d \t %s \t %s \t %d\n", current.locationCode, current.visibilityInArea, current.type, current.sturdiness);
    }
}

static void rawCommandToArguments(char* rawCommand, char commandArguments[][10], int* commandArgumentsCount)
{
    int index = 0;
    int offset = 0;

    char currentArgument[10];
    int charactersReadCount = 0;
    int argumentsReadCount = 0;

    argumentsReadCount = sscanf(rawCommand + offset, "%s%n", &currentArgument, &charactersReadCount);

    while (argumentsReadCount > 0)
    {
        strcpy(commandArguments[index], currentArgument);
        offset += charactersReadCount;
        index++;
        argumentsReadCount = sscanf(rawCommand + offset, "%[^,],%n", &currentArgument, &charactersReadCount);
    }

    *commandArgumentsCount = index;
}

static int processInput(UI* ui, char* inputCommand)
{
    char commandArguments[10][10];
    int commandArgumentsCount;

    rawCommandToArguments(inputCommand, commandArguments, &commandArgumentsCount);

    char* command = commandArguments[0];

    if (strcmp(command, "exit") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "add") == 0)
    {
        add(ui, commandArguments, commandArgumentsCount);
    }
    else if (strcmp(command, "update") == 0)
    {
        update(ui, commandArguments, commandArgumentsCount);
    }
    else if (strcmp(command, "delete") == 0)
    {
        delete(ui, commandArguments, commandArgumentsCount);
    }
    else if (strcmp(command, "list") == 0)
    {
        list(ui, commandArguments, commandArgumentsCount);
    }

    return 0;
}

void UIRun(UI* ui)
{
    char inputCommand[100] = { 0 };
    int result = 0;

    while (result == 0)
    {
        gets(inputCommand);
        result = processInput(ui, inputCommand);
    }
}
