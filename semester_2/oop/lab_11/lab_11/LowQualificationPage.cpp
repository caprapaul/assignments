#include "LowQualificationPage.h"

#include <vector>
#include <string>

#include "Configuration.h"

using namespace std;

void LowQualificationPage::refreshTable()
{
    this->materialsTable->clear();
    QStringList labels;
    labels << "Id" << "Size" << "Infection Level" << "Microfragments Quantity" << "Photograph";
    this->materialsTable->setHorizontalHeaderLabels(labels);
    this->materialsTable->setColumnCount(5);

    QString sizeString = this->sizeLine->text();
    QString microfragmentsQuantityString = this->microfragmentsQuantityLine->text();

    if (sizeString.isEmpty() ||
        microfragmentsQuantityString.isEmpty())
    {
        this->informationLabel->setText(QString::fromStdString(string("<FONT COLOR='#ff0000'>Size and microfragments quantity fields cannot be empty")));
        return;
    }

    string size = sizeString.toStdString();
    int microfragmentsQuantity = microfragmentsQuantityString.toInt();
    this->informationLabel->setText("");

    vector<Material> materials = this->lowQualificationService.GetMaterialsWithSizeAndMicrofragmentsQuantity(size, microfragmentsQuantity);

    this->materialsTable->setRowCount(materials.size());

    int row = 0;
    for (auto currentMaterial : materials)
    {
        //string materialString = currentMaterial.Id() + string(" ") + currentMaterial.Size() + string(" ") + to_string(currentMaterial.InfectionLevel()) + string(" ") + to_string(currentMaterial.MicrofragmentsQuantity()) + string(" ") + currentMaterial.Photograph();
        this->materialsTable->setItem(
            row,
            0,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Id()))
        );
        this->materialsTable->setItem(
            row,
            1,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Size()))
        );
        this->materialsTable->setItem(
            row,
            2,
            new QTableWidgetItem(QString::fromStdString(to_string(currentMaterial.InfectionLevel())))
        );
        this->materialsTable->setItem(
            row,
            3,
            new QTableWidgetItem(QString::fromStdString(to_string(currentMaterial.MicrofragmentsQuantity())))
        );
        this->materialsTable->setItem(
            row,
            4,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Photograph()))
        );

        row++;
    }
}

void LowQualificationPage::setFileButtonClicked()
{
    QString filePathString = this->fileLine->text();
    string filePath = filePathString.toStdString();
    this->lowQualificationService.SetFile(filePath);
}

void LowQualificationPage::setSaveFileButtonClicked()
{
    QString filePathString = this->saveFileLine->text();
    string filePath = filePathString.toStdString();
    this->lowQualificationService.SetSaveFile(filePath);
}

void LowQualificationPage::filterButtonClicked()
{
    this->refreshTable();
}

void LowQualificationPage::nextButtonClicked()
{
    Material nextMaterial;
    QString sizeString = this->nextMaterialLine->text();

    if (sizeString.isEmpty())
    {
        nextMaterial = this->lowQualificationService.GetNextMaterial();
    }
    else
    {
        string size = sizeString.toStdString();

        nextMaterial = this->lowQualificationService.GetNextMaterial(size);
    }
    string materialString = "";
    vector<string> tokens = nextMaterial.Serialize();
    for (int i = 0; i < tokens.size(); i++)
    {
        materialString += tokens[i] + " ";
    }

    this->currentMaterialLabel->setText(QString::fromStdString(materialString));
}

void LowQualificationPage::saveButtonClicked()
{
    QString idString = this->saveIdLine->text();

    if (idString.isEmpty())
    {
        this->informationLabel->setText(QString::fromStdString(string("<FONT COLOR='#ff0000'>Id cannot be empty")));
        return;
    }

    string id = idString.toStdString();

    try 
    {
        this->lowQualificationService.SaveMaterial(id);
        this->informationLabel->setText("Material saved");
    }
    catch (exception& exception)
    {
        this->informationLabel->setText(QString::fromStdString(string("<FONT COLOR='#ff0000'>") + exception.what()));
    }
}

void LowQualificationPage::displaySavedMaterialsButtonClicked()
{
    QWidget* displayWindow = new QWidget();

    QGridLayout* windowLayout = new QGridLayout();
    QTableWidget* savedMaterialsTable = new QTableWidget();

    savedMaterialsTable->setColumnCount(5);
    QStringList labels;
    labels << "Id" << "Size" << "Infection Level" << "Microfragments Quantity" << "Photograph";
    savedMaterialsTable->setHorizontalHeaderLabels(labels);

    vector<Material> materials = this->lowQualificationService.GetSavedMaterials();

    savedMaterialsTable->setRowCount(materials.size());

    int row = 0;
    for (auto currentMaterial : materials)
    {
        //string materialString = currentMaterial.Id() + string(" ") + currentMaterial.Size() + string(" ") + to_string(currentMaterial.InfectionLevel()) + string(" ") + to_string(currentMaterial.MicrofragmentsQuantity()) + string(" ") + currentMaterial.Photograph();
        savedMaterialsTable->setItem(
            row,
            0,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Id()))
        );
        savedMaterialsTable->setItem(
            row,
            1,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Size()))
        );
        savedMaterialsTable->setItem(
            row,
            2,
            new QTableWidgetItem(QString::fromStdString(to_string(currentMaterial.InfectionLevel())))
        );
        savedMaterialsTable->setItem(
            row,
            3,
            new QTableWidgetItem(QString::fromStdString(to_string(currentMaterial.MicrofragmentsQuantity())))
        );
        savedMaterialsTable->setItem(
            row,
            4,
            new QTableWidgetItem(QString::fromStdString(currentMaterial.Photograph()))
        );

        row++;
    }

    windowLayout->addWidget(savedMaterialsTable);

    displayWindow->setLayout(windowLayout);
    displayWindow->show();
}

void LowQualificationPage::openSavedMaterialsButtonClicked()
{
    string filePath = this->lowQualificationService.GetSaveFile();
    string extension = Utility::getFileExtension(filePath);

    if (extension == "csv" || extension == "txt")
    {
        system(string(("notepad.exe ") + filePath).c_str());
    }
    else if (extension == "html")
    {
        system(string(("\"C:\\Program Files\\Mozilla Firefox\\firefox.exe\" ") + filePath).c_str());
    }
}

LowQualificationPage::LowQualificationPage(LowQualificationService& lowQualificationService) :
    lowQualificationService(lowQualificationService)
{
    QGridLayout* pageLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();
    this->sizeLine = new QLineEdit();
    this->microfragmentsQuantityLine = new QLineEdit();
    QPushButton* filterButton = new QPushButton("Filter");
    this->materialsTable = new QTableWidget();
    this->informationLabel = new QLabel();
    this->nextMaterialLine = new QLineEdit();
    this->currentMaterialLabel = new QLabel("None");
    QPushButton* nextButton = new QPushButton("Next");
    this->saveIdLine = new QLineEdit();
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* openSavedMaterialsButton = new QPushButton("Open saved materials file");
    QPushButton* displaySavedMaterialsButton = new QPushButton("Display saved materials");
    this->fileLine = new QLineEdit();
    QPushButton* setFileButton = new QPushButton("Set file location");
    this->saveFileLine = new QLineEdit();
    QPushButton* setSaveFileButton = new QPushButton("Set save file location");

    this->fileLine->setText(QString::fromStdString(this->lowQualificationService.GetFile()));
    this->saveFileLine->setText(QString::fromStdString(this->lowQualificationService.GetSaveFile()));

    QStringList labels;
    labels << "Id" << "Size" << "Infection Level" << "Microfragments Quantity" << "Photograph";
    this->materialsTable->setColumnCount(5);
    this->materialsTable->setHorizontalHeaderLabels(labels);
    this->materialsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->materialsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    this->materialsTable->verticalHeader()->setVisible(false);
    this->materialsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->materialsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QObject::connect(setFileButton, SIGNAL(clicked()), this, SLOT(setFileButtonClicked()));
    QObject::connect(setSaveFileButton, SIGNAL(clicked()), this, SLOT(setSaveFileButtonClicked()));
    QObject::connect(filterButton, SIGNAL(clicked()), this, SLOT(filterButtonClicked()));
    QObject::connect(nextButton, SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
    QObject::connect(openSavedMaterialsButton, SIGNAL(clicked()), this, SLOT(openSavedMaterialsButtonClicked()));
    QObject::connect(displaySavedMaterialsButton, SIGNAL(clicked()), this, SLOT(displaySavedMaterialsButtonClicked()));

    Configuration configuration("config.txt");
    configuration.load();

    formLayout->addRow("Size", this->sizeLine);
    formLayout->addRow("Microfragments Qty.", this->microfragmentsQuantityLine);

    pageLayout->addWidget(new QLabel("Filter materials"), 0, 0);
    pageLayout->addLayout(formLayout, 1, 0, 1, 3);
    pageLayout->addWidget(filterButton, 2, 2, 1, 1);
    pageLayout->addWidget(new QLabel("Materials"), 3, 0);
    pageLayout->addWidget(this->materialsTable, 4, 0, 1, 3);
    pageLayout->addWidget(new QLabel("Size"), 5, 0);
    pageLayout->addWidget(this->nextMaterialLine, 5, 1, 1, 2);
    pageLayout->addWidget(new QLabel("Current material:"), 6, 0);
    pageLayout->addWidget(this->currentMaterialLabel, 6, 1);
    pageLayout->addWidget(nextButton, 6, 2);
    pageLayout->addWidget(new QLabel("Id"), 7, 0);
    pageLayout->addWidget(this->saveIdLine, 7, 1);
    pageLayout->addWidget(saveButton, 7, 2);
    pageLayout->addWidget(this->informationLabel, 8, 0, 1, 3);
    pageLayout->addWidget(openSavedMaterialsButton, 9, 0);
    pageLayout->addWidget(displaySavedMaterialsButton, 9, 1);

    if (configuration.get("repositoryType") == "file")
    {
        pageLayout->addWidget(this->fileLine, 10, 0, 1, 2);
        pageLayout->addWidget(setFileButton, 10, 2);
    }

    if (configuration.get("saveRepositoryType") == "file")
    {
        pageLayout->addWidget(this->saveFileLine, 11, 0, 1, 2);
        pageLayout->addWidget(setSaveFileButton, 11, 2);
    }

    this->setLayout(pageLayout);
}
