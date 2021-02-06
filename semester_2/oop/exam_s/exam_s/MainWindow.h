#pragma once

#include <QtWidgets>

#include "Service.h"
#include "Model.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    Astronomer astronomer;

    Model* model;
    QSortFilterProxyModel* proxyModel;

    QTableView* table;
    QLabel* informationLabel;
    QLineEdit* searchLine;

    //void refreshList();
    void addDialog();
    void updateDialog();
    void deleteDialog();

private slots:
    void addButtonClicked();
    void updateButtonClicked();
    void deleteButtonClicked();
    void refreshButtonClicked();
    void listItemClicked(QModelIndex& item);
    void constellationCheckboxClicked(bool checked);
    void searchTextChanged(const QString& text);

public:
    MainWindow(Astronomer astronomer, Model* model, QWidget *parent = Q_NULLPTR);
};
