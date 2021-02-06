#include "MainWindow.h"

#include <vector>
#include <string>
using namespace std;

MainWindow::MainWindow(HighQualificationService& highQualificationService, LowQualificationService& lowQualificationService, QWidget *parent):
    QWidget(parent),
    highQualificationService(highQualificationService),
    lowQualificationService(lowQualificationService)
{
    QGridLayout* mainLayout = new QGridLayout();
    QTabWidget* pages = new QTabWidget();
    this->highQualificationPage = new HighQualificationPage(this->highQualificationService);
    this->lowQualificationPage = new LowQualificationPage(this->lowQualificationService);

    mainLayout->addWidget(pages);
    pages->addTab(this->highQualificationPage, "High Qualification");
    pages->addTab(this->lowQualificationPage, "Low Qualification");

    this->setLayout(mainLayout);
    this->setMinimumSize(600, 400);
}
