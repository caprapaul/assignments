#pragma once

#include "LowQualificationService.h"
#include <QtWidgets>

class LowQualificationPage : public QWidget
{
    Q_OBJECT

private:
    LowQualificationService& lowQualificationService;

    QLineEdit* fileLine;
    QLineEdit* saveFileLine;
    QTableWidget* materialsTable;
    QLineEdit* sizeLine;
    QLineEdit* microfragmentsQuantityLine;
    QLabel* informationLabel;
    QLineEdit* nextMaterialLine;
    QLabel* currentMaterialLabel;
    QLineEdit* saveIdLine;

    void refreshTable();

public slots:
    void setFileButtonClicked();
    void setSaveFileButtonClicked();
    void filterButtonClicked();
    void nextButtonClicked();
    void saveButtonClicked();
    void displaySavedMaterialsButtonClicked();
    void openSavedMaterialsButtonClicked();

public:
    LowQualificationPage(LowQualificationService& lowQualificationService);
};

