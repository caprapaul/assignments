#include "UI.h"
#include <iostream>

using namespace std;

void UI::mode(vector<string> arguments)
{
    this->serviceMode = arguments[1];
}

void UI::add(vector<string> arguments)
{
    if (this->serviceMode == "A")
    {
        string id = arguments[1];
        string size = arguments[2];

        float infectionLevel;
        try
        {
            infectionLevel = stof(arguments[3]);
        }
        catch (invalid_argument& exception)
        {
            cout << "Invalid infection level." << endl;
            return;
        }

        int microfragmentsQuantity;
        try
        {
            microfragmentsQuantity = stoi(arguments[4]);
        }
        catch (invalid_argument& exception)
        {
            cout << "Invalid microfragments quantity." << endl;
            return;
        }

        string photograph = arguments[5];

        this->highQualificationService.AddMaterial(id, size, infectionLevel, microfragmentsQuantity, photograph);
    }
}

void UI::update(vector<string> arguments)
{
    if (this->serviceMode == "A")
    {
        string id = arguments[1];
        string newSize = arguments[2];

        float newInfectionLevel;
        try
        {
            newInfectionLevel = stof(arguments[3]);
        }
        catch (invalid_argument& exception)
        {
            cout << "Invalid infection level." << endl;
            return;
        }

        int newMicrofragmentsQuantity;
        try
        {
            newMicrofragmentsQuantity = stoi(arguments[4]);
        }
        catch (invalid_argument& exception)
        {
            cout << "Invalid microfragments quantity." << endl;
            return;
        }

        string newPhotograph = arguments[5];

        this->highQualificationService.UpdateMaterial(id, newSize, newInfectionLevel, newMicrofragmentsQuantity, newPhotograph);
    }
}

void UI::remove(vector<string> arguments)
{
    if (this->serviceMode == "A")
    {
        string id = arguments[1];
        this->highQualificationService.RemoveMaterial(id);
    }
}

void UI::list(vector<string> arguments)
{
    if (this->serviceMode == "A")
    {
        vector<Material> materials = this->highQualificationService.GetMaterials();

        for (auto currentMaterial : materials)
        {
            cout << currentMaterial << endl;
        }
    }

    if (this->serviceMode == "B")
    {
        if (arguments.size() < 3)
        {
            return;
        }

        string size = arguments[1];

        int microfragmentsQuantity;
        try
        {
            microfragmentsQuantity = stoi(arguments[2]);
        }
        catch (invalid_argument& exception)
        {
            cout << "Invalid microfragments quantity." << endl;
            return;
        }

        vector<Material> materials = this->lowQualificationService.GetMaterialsWithSizeAndMicrofragmentsQuantity(size, microfragmentsQuantity);

        for (int i = 0; i < materials.size(); i++)
        {
            Material currentMaterial = materials[i];
            cout << currentMaterial << endl;
        }
    }
}

void UI::next(vector<string> arguments)
{
    if (this->serviceMode == "B")
    {
        Material material;
        if (arguments.size() == 1)
        {
            material = this->lowQualificationService.GetNextMaterial();
        }
        else  if (arguments.size() == 2)
        {
            string size = arguments[1];

            try
            {
                material = this->lowQualificationService.GetNextMaterial(size);
            }
            catch (exception& exception)
            {
                cout << exception.what();
            }
        }

        cout << material.Id() << " " << material.Size() << " " << material.InfectionLevel() << " " << material.MicrofragmentsQuantity() << " " << material.Photograph() << endl;
    }
}

void UI::save(vector<string> arguments)
{
    if (this->serviceMode == "B")
    {
        string id = arguments[1];

        this->lowQualificationService.SaveMaterial(id);
    }
}

void UI::mylist(vector<string> arguments)
{
    if (this->serviceMode == "B")
    {
        vector<Material> materials = this->lowQualificationService.GetSavedMaterials();

        for (auto currentMaterial : materials)
        {
            cout << currentMaterial.Id() << " " << currentMaterial.Size() << " " << currentMaterial.InfectionLevel() << " " << currentMaterial.MicrofragmentsQuantity() << " " << currentMaterial.Photograph() << endl;
        }
    }
}

void UI::fileLocation(std::vector<std::string> arguments)
{
    this->filePath = arguments[1];
    this->highQualificationService.SetFile(this->filePath);
}

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
    else if (command == "mode")
    {
        this->mode(commandArguments);
    }
    else if (command == "add")
    {
        this->add(commandArguments);
    }
    else if (command == "update")
    {
        this->update(commandArguments);
    }
    else if (command == "delete")
    {
        this->remove(commandArguments);
    }
    else if (command == "list")
    {
        this->list(commandArguments);
    }
    else if (command == "next")
    {
        this->next(commandArguments);
    }
    else if (command == "save")
    {
        this->save(commandArguments);
    }
    else if (command == "mylist")
    {
        this->mylist(commandArguments);
    }
    else if (command == "fileLocation")
    {
        this->fileLocation(commandArguments);
    }

    return true;
}


UI::UI(HighQualificationService& highQualificationService, LowQualificationService& lowQualificationService) :
    highQualificationService(highQualificationService),
    lowQualificationService(lowQualificationService)
{
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
