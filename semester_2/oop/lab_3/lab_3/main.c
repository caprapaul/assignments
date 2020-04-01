#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "tests.h"
#include "ui.h"

int main()
{
    TestVector();
    TestBarricade();
    TestRepository();
    TestService();

    Repository* repository = NULL;
    Service* service = NULL;
    UI* ui = NULL;

    RepositoryCreate(&repository, BarricadeEqual, BarricadeCopy, BarricadeDestroy);
    ServiceCreate(&service, repository);
    UICreate(&ui, service);

    UIRun(ui);

    RepositoryDestroy(&repository);
    ServiceDestroy(&service);
    UIDestroy(&ui);

    _CrtDumpMemoryLeaks();
    return 0;
}
