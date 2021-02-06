#include "MainWindow.h"
#include "RepositoryCSV.h"
#include <QtWidgets/QApplication>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    shared_ptr<RepositoryCSV<Domain>> repository = make_shared<RepositoryCSV<Domain>>();
    repository->SetFilePath("test.txt");
    Service service(repository);
    service.TestGetNumberOfCarsForManufacturer();

    MainWindow window(service);
    window.show();
    return app.exec();
}
