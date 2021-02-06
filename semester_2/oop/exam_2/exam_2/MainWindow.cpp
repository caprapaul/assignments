#include "MainWindow.h"

using namespace std;

void MainWindow::refreshList()
{
    this->list->clear();
    vector<Domain> elements = this->service.GetAll();

    int row = 0;
    for (auto element : elements)
    {
        vector<string> tokens = element.Serialize();
        string line = "";
        line += tokens[0] + "," + tokens[1];

        this->list->addItem(QString::fromStdString(line));
        this->list->item(row)->setForeground(QColor(QString::fromStdString(element.Color())));

        row++;
    }
}

void MainWindow::addDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* idLine = new QLineEdit();
    QLineEdit* nameLine = new QLineEdit();

    QPushButton* okButton = new QPushButton("Ok");

    if (this->list->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->list->selectionModel()->selectedRows();
        int row = selectedList.at(0).row();
        QString selectedElementString = this->list->item(row)->text();
        vector<string> tokens = Utility::splitString(selectedElementString.toStdString(), ',');

        Domain element;
        element.Deserialize(tokens);

        QString selectedIdString = QString::fromStdString(element.Manufacturer());
        QString selectedNameString = QString::fromStdString(element.Model());

        idLine->setText(selectedIdString);
        nameLine->setText(selectedNameString);
    }

    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    formLayout->addRow("Id", idLine);
    formLayout->addRow("Name", nameLine);

    dialogLayout->addLayout(formLayout, 0, 0, 1, 2);
    dialogLayout->addWidget(okButton);

    dialog->setLayout(dialogLayout);
    dialog->setWindowTitle("Add");

    if (dialog->exec())
    {
        QString idString = idLine->text();
        QString nameString = nameLine->text();

        if (idString.isEmpty() ||
            nameString.isEmpty())
        {
            return;
        }

        string id = idString.toStdString();
        string name = nameString.toStdString();

        //this->service.Add();

        this->refreshList();
    }
}

void MainWindow::updateDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* idLine = new QLineEdit();
    QLineEdit* nameLine = new QLineEdit();
    QPushButton* okButton = new QPushButton("Ok");

    if (this->list->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->list->selectionModel()->selectedRows();
        int row = selectedList.at(0).row();
        QString selectedElementString = this->list->item(row)->text();
        vector<string> tokens = Utility::splitString(selectedElementString.toStdString(), ',');

        Domain element;
        element.Deserialize(tokens);

        QString selectedIdString = QString::fromStdString(element.Manufacturer());
        QString selectedNameString = QString::fromStdString(element.Model());

        idLine->setText(selectedIdString);
        nameLine->setText(selectedNameString);
    }

    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    formLayout->addRow("Id:", idLine);
    formLayout->addItem(new QSpacerItem(0, 10));
    formLayout->addWidget(new QLabel("<b>New values</b>"));
    formLayout->addRow("Name", nameLine);

    dialogLayout->addLayout(formLayout, 0, 0, 1, 2);
    dialogLayout->addWidget(okButton, 1, 1);

    dialog->setLayout(dialogLayout);
    dialog->setWindowTitle("Update");

    if (dialog->exec())
    {
        QString idString = idLine->text();
        QString nameString = nameLine->text();

        if (idString.isEmpty() ||
            nameString.isEmpty())
        {
            return;
        }

        string id = idString.toStdString();
        string name = nameString.toStdString();

        //this->service.Update();

        this->refreshList();
    }
}

void MainWindow::deleteDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* idLine = new QLineEdit();
    QPushButton* okButton = new QPushButton("Ok");

    if (this->list->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->list->selectionModel()->selectedRows();
        int row = selectedList.at(0).row();
        QString selectedElementString = this->list->item(row)->text();
        vector<string> tokens = Utility::splitString(selectedElementString.toStdString(), ',');

        Domain element;
        element.Deserialize(tokens);

        QString selectedIdString = QString::fromStdString(element.Manufacturer());
        QString selectedNameString = QString::fromStdString(element.Model());

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

        //this->service.Delete();

        this->refreshList();
    }
}

void MainWindow::addButtonClicked()
{
    this->addDialog();
}

void MainWindow::updateButtonClicked()
{
    this->updateDialog();
}

void MainWindow::deleteButtonClicked()
{
    this->deleteDialog();
}

void MainWindow::refreshButtonClicked()
{
    this->refreshList();
}

void MainWindow::showCarsButtonClicked()
{
    QString manufacturerString = this->manufacturerLine->text();
    string manufacturer = manufacturerString.toStdString();
    int numberOfCars = this->service.GetNumberOfCarsForManufacturer(manufacturer);

    QString informationString = QString::fromStdString("There are " + to_string(numberOfCars) + " cars from " + manufacturer);
    this->informationLabel->setText(informationString);
}

void MainWindow::listItemClicked(QListWidgetItem * item)
{
    QString selectedElementString = item->text();
    vector<string> tokens = Utility::splitString(selectedElementString.toStdString(), ',');

    this->manufacturerLine->setText(QString::fromStdString(tokens[0]));
}

MainWindow::MainWindow(Service& service, QWidget *parent) :
    QWidget(parent),
    service(service)
{
    QGridLayout* mainLayout = new QGridLayout();
    this->list = new QListWidget();
    QPushButton* addButton = new QPushButton("Add");
    QPushButton* updateButton = new QPushButton("Update");
    QPushButton* deleteButton = new QPushButton("Delete");
    QPushButton* refreshButton = new QPushButton("Refresh");
    this->informationLabel = new QLabel();
    QFormLayout* formLayout = new QFormLayout();
    this->manufacturerLine = new QLineEdit();
    QPushButton* showCarsButton = new QPushButton("Show cars");

    this->list->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->list->setSelectionMode(QAbstractItemView::SingleSelection);
    this->refreshList();

    QObject::connect(this->list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listItemClicked(QListWidgetItem*)));
    QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    QObject::connect(updateButton, SIGNAL(clicked()), this, SLOT(updateButtonClicked()));
    QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    QObject::connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshButtonClicked()));
    QObject::connect(showCarsButton, SIGNAL(clicked()), this, SLOT(showCarsButtonClicked()));

    formLayout->addRow("Manufacturer", this->manufacturerLine);

    mainLayout->addWidget(new QLabel("Cars"), 0, 0);
    mainLayout->addWidget(this->list, 1, 0, 1, 5);
    mainLayout->addWidget(addButton, 0, 2);
    mainLayout->addWidget(updateButton, 0, 3);
    mainLayout->addWidget(deleteButton, 0, 4);
    mainLayout->addWidget(refreshButton, 2, 4);
    mainLayout->addWidget(this->informationLabel, 2, 0, 1, 4);
    mainLayout->addLayout(formLayout, 3, 0, 1, 4);
    mainLayout->addWidget(showCarsButton, 3, 4);

    this->setLayout(mainLayout);
}
