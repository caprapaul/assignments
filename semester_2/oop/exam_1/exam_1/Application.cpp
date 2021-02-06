#include <stdlib.h>
#include <crtdbg.h>

#include "UI.h"

int main()
{
    Repository<std::shared_ptr<HospitalDepartment>> repository;
    Controller controller(repository);
    UI ui(controller);

    ui.Run();
}
