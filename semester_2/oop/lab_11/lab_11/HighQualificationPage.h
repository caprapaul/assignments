#pragma once

#include "HighQualificationService.h"
#include <QtWidgets>

class HighQualificationPage : public QWidget
{
    Q_OBJECT

private:
    HighQualificationService& highQualificationService;

    QLineEdit* fileLine;
    QTableWidget* materialsTable;
    QLabel* informationLabel;

    void refreshTable();
    void addDialog();
    void updateDialog();
    void deleteDialog();

public slots:
    void setFileButtonClicked();
    void addButtonClicked();
    void updateButtonClicked();
    void deleteButtonClicked();
    void refreshButtonClicked();

public:
    HighQualificationPage(HighQualificationService& highQualificationService);

};

