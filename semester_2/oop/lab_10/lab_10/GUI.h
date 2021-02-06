#pragma once

#include "HighQualificationService.h"
#include "LowQualificationService.h"
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>

class GUI: public QWidget
{
    Q_OBJECT

private:
    HighQualificationService& highQualificationService;
    LowQualificationService& lowQualificationService;

    QTableWidget* materialsTableWidget;


public:
    GUI(HighQualificationService& highQualificationService, LowQualificationService& lowQualificationService, QWidget* parent = nullptr);
    ~GUI();

    void populateList();
};

