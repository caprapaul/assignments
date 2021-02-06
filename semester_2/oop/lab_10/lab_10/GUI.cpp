#include "GUI.h"
#include <QtWidgets>
#include <vector>
#include <string>
using namespace std;

GUI::GUI(HighQualificationService& highQualificationService, LowQualificationService& lowQualificationService, QWidget* parent) :
    QWidget(parent),
    highQualificationService(highQualificationService),
    lowQualificationService(lowQualificationService)
{
    this->materialsTableWidget = new QTableWidget();
    this->materialsTableWidget->setColumnCount(5);

    QStringList labels;
    labels << "Id" << "Size" << "Infection Level" << "Microfragments Quantity" << "Photograph";

    this->materialsTableWidget->setHorizontalHeaderLabels(labels);
    this->materialsTableWidget->verticalHeader()->setVisible(false);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(new QLabel("All materials"));
    mainLayout->addWidget(this->materialsTableWidget);

    QFormLayout* addFormLayout = new QFormLayout();
    addFormLayout->addRow("Id:", new QLineEdit());
    addFormLayout->addRow("Size:", new QLineEdit());
    addFormLayout->addRow("Infection Level:", new QLineEdit());
    addFormLayout->addRow("Microfragments Quantity:", new QLineEdit());
    addFormLayout->addRow("Photograph:", new QLineEdit());

    mainLayout->addLayout(addFormLayout, 2, 0);

    mainLayout->addWidget(new QPushButton("Add"), 3, 0);
    mainLayout->addWidget(new QPushButton("Delete"), 4, 0);
    mainLayout->addWidget(new QPushButton("Update"), 5, 0);
    mainLayout->addWidget(new QPushButton("Filter"), 6, 0);

    this->setLayout(mainLayout);

    this->highQualificationService.SetFile("test.txt");
    this->lowQualificationService.SetSaveFile("test_run.csv");

    this->populateList();
}

GUI::~GUI()
{
}

void GUI::populateList()
{
    this->materialsTableWidget->clear();
    vector<Material> materials = this->highQualificationService.GetMaterials();

    QStringList labels;
    labels << "Id" << "Size" << "Infection Level" << "Microfragments Quantity" << "Photograph";

    this->materialsTableWidget->setHorizontalHeaderLabels(labels);
    this->materialsTableWidget->setRowCount(materials.size());

    int row = 0;
    for (auto currentMaterial : materials)
    {
        //string materialString = currentMaterial.Id() + string(" ") + currentMaterial.Size() + string(" ") + to_string(currentMaterial.InfectionLevel()) + string(" ") + to_string(currentMaterial.MicrofragmentsQuantity()) + string(" ") + currentMaterial.Photograph();
        this->materialsTableWidget->setItem(
            row, 
            0, 
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Id()))
        );
        this->materialsTableWidget->setItem(
            row,
            1,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Size()))
        );
        this->materialsTableWidget->setItem(
            row,
            2,
            new QTableWidgetItem(QString::fromStdString(to_string(currentMaterial.InfectionLevel())))
        );
        this->materialsTableWidget->setItem(
            row,
            3,
            new QTableWidgetItem(QString::fromStdString(to_string(currentMaterial.MicrofragmentsQuantity())))
        );
        this->materialsTableWidget->setItem(
            row,
            4,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Photograph()))
        );

        row++;
    }
}
