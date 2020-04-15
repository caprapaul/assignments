#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

#include "UI.h"
#include "Tests.h"

int main()
{
    Tests tests;
    tests.RunAll();

    //Repository<Material> repository;
    //HighQualificationService highQualificationService(repository);
    //LowQualificationService lowQualificationService(repository);
    //UI ui(highQualificationService, lowQualificationService);

    //ui.Run();
}
