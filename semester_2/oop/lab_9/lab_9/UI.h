#pragma once

#include "HighQualificationService.h"
#include "LowQualificationService.h"
#include "Utility.h"
#include <string>

class UI
{
private:
    HighQualificationService& highQualificationService;
    LowQualificationService& lowQualificationService;

    std::string serviceMode;

    void mode(std::vector<std::string> arguments);
    void add(std::vector<std::string> arguments);
    void update(std::vector<std::string> arguments);
    void remove(std::vector<std::string> arguments);
    void list(std::vector<std::string> arguments);
    void next(std::vector<std::string> arguments);
    void save(std::vector<std::string> arguments);
    void myList(std::vector<std::string> arguments);
    void myListLocation(std::vector<std::string> arguments);
    void fileLocation(std::vector<std::string> arguments);

    bool processInput(std::string input);

public:
    UI(HighQualificationService& highQualificationService, LowQualificationService& lowQualificationService);
    ~UI();

    void Run();
};

