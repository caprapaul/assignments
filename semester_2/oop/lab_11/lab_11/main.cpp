#include "MainWindow.h"
#include "Configuration.h"
#include "RepositoryMemory.h"
#include "RepositoryCSV.h"
#include "RepositoryHTML.h"
#include <QtWidgets/QApplication>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Configuration configuration("config.txt");
    configuration.load();
   
    string repositoryType = configuration.get("repositoryType");
    string fileLocation = configuration.get("fileLocation");
    shared_ptr<Repository<Material>> repository;

    if (repositoryType == "file")
    {
        string extension = Utility::getFileExtension(fileLocation);

        if (extension == "csv")
        {
            repository = make_shared<RepositoryCSV<Material>>();
        }
        else if (extension == "html")
        {
            repository = make_shared<RepositoryHTML<Material>>
            (
                "Saved Materials",
                vector<string>
                {
                    "Id",
                    "Size",
                    "Infection Level",
                    "Microfragments Quantity",
                    "Photograph"
                }
            );
        }
        else
        {
            repository = make_shared<RepositoryCSV<Material>>();
        }
    }
    else
    {
        repository = make_shared<RepositoryMemory<Material>>();
    }

    string saveRepositoryType = configuration.get("saveRepositoryType");
    string saveFileLocation = configuration.get("saveFileLocation");
    shared_ptr<Repository<Material>> saveRepository;

    if (saveRepositoryType == "file")
    {
        string extension = Utility::getFileExtension(fileLocation);

        if (extension == "csv")
        {
            repository = make_shared<RepositoryCSV<Material>>();
        }
        else if (extension == "html")
        {
            repository = make_shared<RepositoryHTML<Material>>
            (
                "Saved Materials", 
                vector<string> 
                { 
                    "Id", 
                    "Size", 
                    "Infection Level", 
                    "Microfragments Quantity",
                    "Photograph"
                }
            );
        }
        else
        {
            repository = make_shared<RepositoryCSV<Material>>();
        }
    }
    else
    {
        saveRepository = make_shared<RepositoryMemory<Material>>();
    }

    HighQualificationService highQualificationService(repository);
    LowQualificationService lowQualificationService(repository, saveRepository);

    if (repositoryType == "file")
    {
        highQualificationService.SetFile(fileLocation);
        lowQualificationService.SetFile(fileLocation);
    }

    if (saveRepositoryType == "file")
    {
        lowQualificationService.SetSaveFile(saveFileLocation);
    }

    MainWindow mainWindow(highQualificationService, lowQualificationService);
    mainWindow.show();
    return app.exec();
}
