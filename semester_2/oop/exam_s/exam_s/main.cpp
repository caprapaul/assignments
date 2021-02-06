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

    shared_ptr<RepositoryCSV<Astronomer>> repositoryAstronomers = make_shared<RepositoryCSV<Astronomer>>();
    repositoryAstronomers->SetFilePath("test_astronomers.txt");

    Service service(repository, repositoryAstronomers);
    Model* model = new Model(service);

    vector<Astronomer> astronomers = service.GetAllAstronomers();

    vector<MainWindow*> windows;

    for (Astronomer astronomer : astronomers)
    {
        MainWindow* window = new MainWindow(astronomer, model);
        window->show();
        windows.push_back(window);
    }
    
    //MainWindow window2(service);
    //window2.show();
    int result = app.exec();

    service.SaveSorted();
    return result;
}
