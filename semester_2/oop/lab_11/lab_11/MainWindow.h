#pragma once

#include "HighQualificationService.h"
#include "LowQualificationService.h"
#include "HighQualificationPage.h"
#include "LowQualificationPage.h"
#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    HighQualificationService& highQualificationService;
    LowQualificationService& lowQualificationService;

    HighQualificationPage* highQualificationPage;
    LowQualificationPage* lowQualificationPage;

public:
    MainWindow(HighQualificationService& highQualificationService, LowQualificationService& lowQualificationService, QWidget *parent = Q_NULLPTR);
};
