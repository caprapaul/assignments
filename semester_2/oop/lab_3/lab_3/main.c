#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "vector_test.h"
#include "ui.h"

int main()
{
    TestVector();

    Repository* repository = NULL;
    Service* service = NULL;
    UI* ui = NULL;

    RepositoryCreate(&repository, BarricadeCompare, BarricadeCopy);
    ServiceCreate(&service, repository);
    UICreate(&ui, service);

    UIRun(ui);

    RepositoryDestroy(&repository, BarricadeDestroy);
    ServiceDestroy(&service);
    UIDestroy(&ui);

    _CrtDumpMemoryLeaks();
    return 0;
}
