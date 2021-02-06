#include <QtWidgets/QApplication>
#include "UI.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    std::shared_ptr<RepositoryText> repository = std::make_shared<RepositoryText>();
    HighQualificationService highQualificationService(repository);
    LowQualificationService lowQualificationService(repository);
    GUI gui(highQualificationService, lowQualificationService);

    gui.show();
    return application.exec();
}
