#include "Domain.h"

using namespace std;

Domain::Domain()
{
    this->manufacturer = "";
    this->model = "";
}

Domain::Domain(string id, string name, int fabricationYear, std::string color)
{
    this->manufacturer = id;
    this->model = name;
    this->fabricationYear = fabricationYear;
    this->color = color;
}

Domain::~Domain()
{
}

string Domain::Manufacturer()
{
    return this->manufacturer;
}

string Domain::Model()
{
    return this->model;
}

int Domain::FabricationYear()
{
    return this->fabricationYear;
}

std::string Domain::Color()
{
    return this->color;
}

vector<string> Domain::Serialize()
{
    return vector<string>
    {
        this->manufacturer,
        this->model,
        to_string(this->fabricationYear),
        this->color
    };
}

void Domain::Deserialize(vector<string> tokens)
{
    this->manufacturer = tokens[0];
    this->model = tokens[1];
    this->fabricationYear = stoi(tokens[2]);
    this->color = tokens[3];
}
