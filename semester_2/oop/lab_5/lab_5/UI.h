#pragma once

#include "HighQualificationService.h"
#include "LowQualificationService.h"
#include <string>

class UI
{
private:
    HighQualificationService& highQualificationService;
    LowQualificationService& lowQualificationService;

    std::string serviceMode;

    void mode(Vector<std::string> arguments);
    void add(Vector<std::string> arguments);
    void update(Vector<std::string> arguments);
    void remove(Vector<std::string> arguments);
    void list(Vector<std::string> arguments);
    void next(Vector<std::string> arguments);
    void save(Vector<std::string> arguments);
    void mylist(Vector<std::string> arguments);

    bool processInput(std::string input);

public:
    UI(HighQualificationService& highQualificationService, LowQualificationService& lowQualificationService);
    ~UI();

    void Run();
};

