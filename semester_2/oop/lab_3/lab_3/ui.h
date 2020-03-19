#pragma once
#include "service.h"

typedef struct
{
    Service* service;
} UI;

int UICreate(UI** ui, Service* service);
int UIDestroy(UI** ui);

void UIRun(UI* ui);
