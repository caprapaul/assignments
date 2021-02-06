#include "HighQualificationPage.h"

#include <vector>
#include <string>

#include "Configuration.h"

using namespace std;

void HighQualificationPage::refreshTable()
{
    this->materialsTable->clear();
    vector<Material> materials = this->highQualificationService.GetMaterials();

    QStringList labels;
    labels << "Id" << "Size" << "Infection Level" << "Microfragments Quantity" << "Photograph";
    this->materialsTable->setHorizontalHeaderLabels(labels);
    this->materialsTable->setColumnCount(5);
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

void HighQualificationPage::addDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* idLine = new QLineEdit();
    QLineEdit* sizeLine = new QLineEdit();
    QLineEdit* infectionLine = new QLineEdit();
    QLineEdit* microfragmentsLine = new QLineEdit();
    QLineEdit* photographLine = new QLineEdit();
    QPushButton* okButton = new QPushButton("Ok");

    if (this->materialsTable->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->materialsTable->selectionModel()->selectedRows();
        int row = selectedList.at(0).row();
        QString selectedIdString = this->materialsTable->item(row, 0)->text();
        QString selectedSizeString = this->materialsTable->item(row, 1)->text();
        QString selectedInfectionString = this->materialsTable->item(row, 2)->text();
        QString selectedMicrofragmentsString = this->materialsTable->item(row, 3)->text();
        QString selectedPhotographString = this->materialsTable->item(row, 4)->text();

        idLine->setText(selectedIdString);
        sizeLine->setText(selectedSizeString);
        infectionLine->setText(selectedInfectionString);
        microfragmentsLine->setText(selectedMicrofragmentsString);
        photographLine->setText(selectedPhotographString);
    }

    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    formLayout->addRow("Id", idLine);
    formLayout->addRow("Size", sizeLine);
    formLayout->addRow("Infection Level", infectionLine);
    formLayout->addRow("Microfragments Quantity", microfragmentsLine);
    formLayout->addRow("Photograph", photographLine);

    dialogLayout->addLayout(formLayout, 0, 0, 1, 2);
    dialogLayout->addWidget(okButton);

    dialog->setLayout(dialogLayout);
    dialog->setWindowTitle("Add");

    if (dialog->exec())
    {
        QString idString = idLine->text();
        QString sizeString = sizeLine->text();
        QString infectionLevelString = infectionLine->text();
        QString microfragmentsQuantityString = microfragmentsLine->text();
        QString photographString = photographLine->text();

        if (idString.isEmpty() ||
            sizeString.isEmpty() ||
            infectionLevelString.isEmpty() ||
            microfragmentsQuantityString.isEmpty() ||
            photographString.isEmpty())
        {
            return;
        }

        string id = idString.toStdString();
        string size = sizeString.toStdString();
        float infectionLevel = infectionLevelString.toFloat();
        int microfragmentsQuantity = microfragmentsQuantityString.toInt();
        string photograph = photographString.toStdString();

        try
        {
            this->highQualificationService.AddMaterial(id, size, infectionLevel, microfragmentsQuantity, photograph);
        }
        catch (exception& exception)
        {
            this->informationLabel->setText(QString::fromStdString(string("<FONT COLOR='#ff0000'>") + exception.what()));
            return;
        }

        this->refreshTable();
        this->informationLabel->setText(QString::fromStdString(string("Added material with id: ") + id));
    }
}

void HighQualificationPage::updateDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* idLine = new QLineEdit();
    QLineEdit* sizeLine = new QLineEdit();
    QLineEdit* infectionLine = new QLineEdit();
    QLineEdit* microfragmentsLine = new QLineEdit();
    QLineEdit* photographLine = new QLineEdit();
    QPushButton* okButton = new QPushButton("Ok");

    if (this->materialsTable->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->materialsTable->selectionModel()->selectedRows();
        int row = selectedList.at(0).row();
        QString selectedIdString = this->materialsTable->item(row, 0)->text();
        QString selectedSizeString = this->materialsTable->item(row, 1)->text();
        QString selectedInfectionString = this->materialsTable->item(row, 2)->text();
        QString selectedMicrofragmentsString = this->materialsTable->item(row, 3)->text();
        QString selectedPhotographString = this->materialsTable->item(row, 4)->text();

        idLine->setText(selectedIdString);
        sizeLine->setText(selectedSizeString);
        infectionLine->setText(selectedInfectionString);
        microfragmentsLine->setText(selectedMicrofragmentsString);
        photographLine->setText(selectedPhotographString);
    }

    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    formLayout->addRow("Id:", idLine);
    formLayout->addItem(new QSpacerItem(0, 10));
    formLayout->addWidget(new QLabel("<b>New values</b>"));
    formLayout->addRow("Size", sizeLine);
    formLayout->addRow("Infection Level", infectionLine);
    formLayout->addRow("Microfragments Quantity", microfragmentsLine);
    formLayout->addRow("Photograph", photographLine);

    dialogLayout->addLayout(formLayout, 0, 0, 1, 2);
    dialogLayout->addWidget(okButton, 1, 1);

    dialog->setLayout(dialogLayout);
    dialog->setWindowTitle("Update");

    if (dialog->exec())
    {
        QString idString = idLine->text();
        QString sizeString = sizeLine->text();
        QString infectionLevelString = infectionLine->text();
        QString microfragmentsQuantityString = microfragmentsLine->text();
        QString photographString = photographLine->text();

        if (idString.isEmpty() ||
            sizeString.isEmpty() ||
            infectionLevelString.isEmpty() ||
            microfragmentsQuantityString.isEmpty() ||
            photographString.isEmpty())
        {
            return;
        }

        string id = idString.toStdString();
        string size = sizeString.toStdString();
        float infectionLevel = infectionLevelString.toFloat();
        int microfragmentsQuantity = microfragmentsQuantityString.toInt();
        string photograph = photographString.toStdString();

        this->highQualificationService.UpdateMaterial(id, size, infectionLevel, microfragmentsQuantity, photograph);
        this->informationLabel->setText(QString::fromStdString(string("Updated material with id: ") + id));
        this->refreshTable();
    }
}

void HighQualificationPage::deleteDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* idLine = new QLineEdit();
    QLineEdit* sizeLine = new QLineEdit();
    QLineEdit* infectionLine = new QLineEdit();
    QLineEdit* microfragmentsLine = new QLineEdit();
    QLineEdit* photographLine = new QLineEdit();
    QPushButton* okButton = new QPushButton("Ok");

    if (this->materialsTable->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->materialsTable->selectionModel()->selectedRows();
        int row = selectedList.at(0).row();
        QString selectedIdString = this->materialsTable->item(row, 0)->text();

        idLine->setText(selectedIdString);
    }

    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    formLayout->addRow("Id:", idLine);

    dialogLayout->addLayout(formLayout, 0, 0, 1, 2);
    dialogLayout->addWidget(okButton, 1, 1);

    dialog->setLayout(dialogLayout);
    dialog->setWindowTitle("Delete");

    if (dialog->exec())
    {
        QString idString = idLine->text();

        if (idString.isEmpty())
        {
            return;
        }

        string id = idString.toStdString();

        this->highQualificationService.RemoveMaterial(id);
        this->informationLabel->setText(QString::fromStdString(string("Deleted material with id: ") + id));
        this->refreshTable();
    }
}

void HighQualificationPage::setFileButtonClicked()
{
    QString filePathString = this->fileLine->text();
    string filePath = filePathString.toStdString();
    this->highQualificationService.SetFile(filePath);
    this->refreshTable();
}

void HighQualificationPage::addButtonClicked()
{
    this->addDialog();
}

void HighQualificationPage::updateButtonClicked()
{
    this->updateDialog();
}

void HighQualificationPage::deleteButtonClicked()
{
    this->deleteDialog();
}

void HighQualificationPage::refreshButtonClicked()
{
    this->refreshTable();
}

HighQualificationPage::HighQualificationPage(HighQualificationService& highQualificationService) :
    highQualificationService(highQualificationService)
{
    QGridLayout* pageLayout = new QGridLayout();
    this->materialsTable = new QTableWidget();
    QPushButton* addButton = new QPushButton("Add");
    QPushButton* updateButton = new QPushButton("Update");
    QPushButton* deleteButton = new QPushButton("Delete");
    QPushButton* refreshButton = new QPushButton("Refresh");
    this->fileLine = new QLineEdit();
    QPushButton* setFileButton = new QPushButton("Set file location");
    this->informationLabel = new QLabel("");

    this->materialsTable->setColumnCount(5);
    this->materialsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->materialsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    this->materialsTable->verticalHeader()->setVisible(false);
    this->materialsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->materialsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->refreshTable();

    this->fileLine->setText(QString::fromStdString(this->highQualificationService.GetFile()));

    QObject::connect(setFileButton, SIGNAL(clicked()), this, SLOT(setFileButtonClicked()));
    QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    QObject::connect(updateButton, SIGNAL(clicked()), this, SLOT(updateButtonClicked()));
    QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    QObject::connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshButtonClicked()));

    pageLayout->addWidget(new QLabel("Materials"), 0, 0);
    pageLayout->addWidget(this->materialsTable, 1, 0, 1, 5);
    pageLayout->addWidget(addButton, 0, 2);
    pageLayout->addWidget(updateButton, 0, 3);
    pageLayout->addWidget(deleteButton, 0, 4);
    pageLayout->addWidget(refreshButton, 2, 4);
    pageLayout->addWidget(this->informationLabel, 2, 0);

    Configuration configuration("config.txt");
    configuration.load();

    if (configuration.get("repositoryType") == "file")
    {
        pageLayout->addWidget(this->fileLine, 3, 0, 1, 4);
        pageLayout->addWidget(setFileButton, 3, 4);
    }

    this->setLayout(pageLayout);
}
