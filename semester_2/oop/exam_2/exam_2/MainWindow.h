#pragma once

#include <QtWidgets>

#include "Service.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    Service& service;

    QListWidget* list;
    QLineEdit* manufacturerLine;
    QLabel* informationLabel;

    void refreshList();
    void addDialog();
    void updateDialog();
    void deleteDialog();

public slots:
    void addButtonClicked();
    void updateButtonClicked();
    void deleteButtonClicked();
    void refreshButtonClicked();
    void showCarsButtonClicked();
    void listItemClicked(QListWidgetItem* item);

public:
    MainWindow(Service& service, QWidget *parent = Q_NULLPTR);
};
