#include <stdio.h>
#include <stdlib.h>

#include "ui.h"

int main()
{
    Repository* repository = NULL;
    Service* service = NULL;
    UI* ui = NULL;

    RepositoryCreate(&repository, BarricadeCompare);
    ServiceCreate(&service, repository);
    UICreate(&ui, service);

    UIRun(ui);

    return 0;
}
