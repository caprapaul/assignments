#include "MainWindow.h"

using namespace std;

void MainWindow::addDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* nameLine = new QLineEdit();
    QLineEdit* raLine = new QLineEdit();
    QLineEdit* decLine = new QLineEdit();
    QLineEdit* diameterLine = new QLineEdit();

    QPushButton* okButton = new QPushButton("Ok");

    if (this->table->selectionModel()->hasSelection())
    {
        int selectedRow = this->table->selectionModel()->selectedRows().at(0).row();
        QString selectedNameString = this->model->data(this->model->index(selectedRow, 0), Qt::DisplayRole).toString();
        QString selectedRaString = this->model->data(this->model->index(selectedRow, 2), Qt::DisplayRole).toString();
        QString selectedDecString = this->model->data(this->model->index(selectedRow, 3), Qt::DisplayRole).toString();
        QString selectedDiameterString = this->model->data(this->model->index(selectedRow, 4), Qt::DisplayRole).toString();

        nameLine->setText(selectedNameString);
        raLine->setText(selectedRaString);
        decLine->setText(selectedDecString);
        diameterLine->setText(selectedDiameterString);
    }

    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    formLayout->addRow("Name", nameLine);
    formLayout->addRow("Right Ascension", raLine);
    formLayout->addRow("Declination", decLine);
    formLayout->addRow("Diameter", diameterLine);

    dialogLayout->addLayout(formLayout, 0, 0, 1, 2);
    dialogLayout->addWidget(okButton);

    dialog->setLayout(dialogLayout);
    dialog->setWindowTitle("Add");

    if (dialog->exec())
    {
        QString nameString = nameLine->text();
        QString raString = raLine->text();
        QString decString = decLine->text();
        QString diameterString = diameterLine->text();

        if (nameString.isEmpty())
        {
            return;
        }

        string name = nameString.toStdString();
        string constellation = this->astronomer.Constellation();
        int ra = raString.toInt();
        int dec = decString.toInt();
        int diameter = diameterString.toInt();

        try
        {
            this->model->AddStar(name, constellation, ra, dec, diameter);
        }
        catch (exception& exception)
        {
            this->informationLabel->setText(QString::fromStdString(string("<FONT COLOR='#ff0000'>") + exception.what()));
            return;
        }
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

    if (this->table->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->table->selectionModel()->selectedRows();
        QModelIndex row = selectedList.first();
        QString selectedElementString = row.data(Qt::DisplayRole).toString();
        vector<string> tokens = Utility::splitString(selectedElementString.toStdString(), ',');

        Domain element;
        element.Deserialize(tokens);

        //QString selectedIdString = QString::fromStdString(element.Manufacturer());
        //QString selectedNameString = QString::fromStdString(element.Model());

        //idLine->setText(selectedIdString);
        //nameLine->setText(selectedNameString);
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

        //this->refreshList();
    }
}

void MainWindow::deleteDialog()
{
    QDialog* dialog = new QDialog();
    QGridLayout* dialogLayout = new QGridLayout();
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* idLine = new QLineEdit();
    QPushButton* okButton = new QPushButton("Ok");

    if (this->table->selectionModel()->hasSelection())
    {
        QModelIndexList selectedList = this->table->selectionModel()->selectedRows();
        QModelIndex row = selectedList.first();
        QString selectedElementString = row.data(Qt::DisplayRole).toString();
        vector<string> tokens = Utility::splitString(selectedElementString.toStdString(), ',');

        Domain element;
        element.Deserialize(tokens);

        //QString selectedIdString = QString::fromStdString(element.Manufacturer());
        //QString selectedNameString = QString::fromStdString(element.Model());

        //idLine->setText(selectedIdString);
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

        //this->refreshList();
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
    //this->refreshList();
}

void MainWindow::listItemClicked(QModelIndex& item)
{
    QString selectedElementString = item.data().toString();
    vector<string> tokens = Utility::splitString(selectedElementString.toStdString(), ',');

}

void MainWindow::constellationCheckboxClicked(bool checked)
{
    if (checked)
    {
        this->proxyModel->setFilterRegExp(QRegExp(QString::fromStdString(astronomer.Constellation()), Qt::CaseInsensitive, QRegExp::FixedString));
        this->proxyModel->setFilterKeyColumn(1);
    }
    else
    {
        this->proxyModel->setFilterRegExp("");
    }
}

void MainWindow::searchTextChanged(const QString & text)
{
    if (text.isEmpty())
    {
        this->proxyModel->setFilterRegExp("");
    }
    else
    {
        this->proxyModel->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
        this->proxyModel->setFilterKeyColumn(0);
    }
}

MainWindow::MainWindow(Astronomer astronomer, Model* model, QWidget *parent) :
    QWidget(parent),
    astronomer(astronomer),
    model(model)
{
    //this->model = new Model(this->service);
    this->proxyModel = new QSortFilterProxyModel();
    this->proxyModel->setSourceModel(this->model);

    QGridLayout* mainLayout = new QGridLayout();
    this->table = new QTableView();
    QPushButton* addButton = new QPushButton("Add");
    QPushButton* updateButton = new QPushButton("Update");
    QPushButton* deleteButton = new QPushButton("Delete");
    QPushButton* refreshButton = new QPushButton("Refresh");
    this->informationLabel = new QLabel();
    QCheckBox* constellationCheckbox = new QCheckBox("Toggle self constellation", this);
    QLabel* searchLabel = new QLabel("Search name:");
    this->searchLine = new QLineEdit();

    this->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->table->setSelectionMode(QAbstractItemView::SingleSelection);
    this->table->setSortingEnabled(true);

    this->table->setModel(this->proxyModel);
    this->table->hideColumn(1);
    //this->refreshList();

    QObject::connect(this->table->selectionModel(), SIGNAL(clicked(const QModelIndex)), this, SLOT(listItemClicked(QModelIndex)));
    QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    QObject::connect(updateButton, SIGNAL(clicked()), this, SLOT(updateButtonClicked()));
    QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    QObject::connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshButtonClicked()));
    QObject::connect(constellationCheckbox, SIGNAL(clicked(bool)), this, SLOT(constellationCheckboxClicked(bool)));
    QObject::connect(this->searchLine, SIGNAL(textChanged(QString)), this, SLOT(searchTextChanged(QString)));

    mainLayout->addWidget(new QLabel("Stars"), 0, 0);
    mainLayout->addWidget(this->table, 1, 0, 1, 5);
    mainLayout->addWidget(addButton, 0, 2);
    mainLayout->addWidget(updateButton, 0, 3);
    mainLayout->addWidget(deleteButton, 0, 4);
    mainLayout->addWidget(refreshButton, 2, 4);
    mainLayout->addWidget(this->informationLabel, 2, 0, 1, 4);
    mainLayout->addWidget(constellationCheckbox, 3, 0, 1, 4);
    mainLayout->addWidget(searchLabel, 4, 0);
    mainLayout->addWidget(this->searchLine, 4, 1);

    this->setMinimumWidth(420);
    this->setWindowTitle(QString::fromStdString(this->astronomer.Name()));
    this->setLayout(mainLayout);
}
