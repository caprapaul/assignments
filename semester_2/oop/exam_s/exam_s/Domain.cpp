#include "Domain.h"

using namespace std;

Domain::Domain()
{

}

Domain::Domain(std::string name, std::string constellation, int rightAscension, int declination, int diameter)
{
    this->name = name;
    this->constellation = constellation;
    this->rightAscension = rightAscension;
    this->declination = declination;
    this->diameter = diameter;
}

Domain::~Domain()
{
}

string Domain::Name()
{
    return this->name;
}

string Domain::Constellation()
{
    return this->constellation;
}

int Domain::RA()
{
    return this->rightAscension;
}

int Domain::Dec()
{
    return this->declination;
}

int Domain::Diameter()
{
    return this->diameter;
}

vector<string> Domain::Serialize()
{
    return vector<string>
    {
        this->name,
        this->constellation,
        to_string(this->rightAscension),
        to_string(this->declination),
        to_string(this->diameter)
    };
}

void Domain::Deserialize(vector<string> tokens)
{
    this->name = tokens[0];
    this->constellation = tokens[1];
    this->rightAscension = stoi(tokens[2]);
    this->declination = stoi(tokens[3]);
    this->diameter = stoi(tokens[4]);
}
