#include "UI.h"

#include <iostream>

using namespace std;

vector<string> rawCommandToArguments(string rawCommand)
{
    vector<string> arguments;

    char* rawCommandCString = new char[rawCommand.size() + 1];
    strcpy(rawCommandCString, rawCommand.c_str());

    int position = rawCommand.find(" ");
    string token = rawCommand.substr(0, position);
    arguments.push_back(token);
    rawCommand.erase(0, position + 1);

    while (position != string::npos)
    {
        position = rawCommand.find(", ");
        token = rawCommand.substr(0, position);
        arguments.push_back(token);
        rawCommand.erase(0, position + 2);
    }

    return arguments;
}

// Returns false if the program should exit.
bool UI::processInput(string input)
{
    vector<string> commandArguments = rawCommandToArguments(input);

    string command = commandArguments[0];

    if (command == "exit")
    {
        return false;
    }
    else if (command == "add")
    {
        this->add(commandArguments);
    }
    else if (command == "list")
    {
        this->list(commandArguments);
    }
    else if (command == "fileLocation")
    {
        this->fileLocation(commandArguments);
    }

    return true;
}

void UI::add(vector<string> arguments)
{
    string mallSection = arguments[1];
    string departmentType = arguments[2];

    if (departmentType == "Surgery")
    {
        int numberOfDoctors = stoi(arguments[3]);
        int numberOfPatients = stoi(arguments[4]);

        this->controller.AddDepartment(shared_ptr<HospitalDepartment>(new Surgery(mallSection, numberOfDoctors, numberOfPatients)));
    }

    if (departmentType == "Neonatal Unit")
    {
        int numberOfDoctors = stoi(arguments[3]);
        int numberOfMothers = stoi(arguments[4]);
        int numberOfBabies = stoi(arguments[5]);
        int averageGrade = stod(arguments[6]);

        //this->controller.AddDepartment(make_shared<HospitalDepartment>(new NeonatalUnit(mallSection, numberOfDoctors, numberOfPatients)));
    }
}

void UI::list(std::vector<std::string> arguments)
{
    vector<HospitalDepartment> departments = this->controller.GetAllDepartments();

    int elementIndex = 0;
    for (auto department : departments)
    {
        cout << department.ToString();

        if (elementIndex < departments.size() - 1)
        {
            cout << std::endl;
        }

        elementIndex++;
    }
}

void UI::fileLocation(vector<string> arguments)
{
}

UI::UI(Controller controller)
{
    this->controller = controller;
}

UI::~UI()
{
}

void UI::Run()
{
    string input;
    bool continueLoop = true;

    while (continueLoop)
    {
        getline(cin, input);
        continueLoop = this->processInput(input);
    }
}
