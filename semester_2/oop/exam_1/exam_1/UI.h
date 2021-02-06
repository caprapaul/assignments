#pragma once

#include "Controller.h"
#include <string>
#include "Surgery.h"
#include "NeonatalUnit.h"

class UI
{
private:
    Controller controller;

    bool processInput(std::string input);

    void add(std::vector<std::string> arguments);
    void list(std::vector<std::string> arguments);
    void fileLocation(std::vector<std::string> arguments);

public:
    UI(Controller controller);
    ~UI();

    void Run();
};

