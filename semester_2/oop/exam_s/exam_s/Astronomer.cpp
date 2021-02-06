#include "Astronomer.h"

using namespace std;

Astronomer::Astronomer()
{
}

Astronomer::Astronomer(std::string name, std::string constellation)
{
    this->name = name;
    this->constellation = constellation;
}

Astronomer::~Astronomer()
{
}

string Astronomer::Name()
{
    return this->name;
}

string Astronomer::Constellation()
{
    return this->constellation;
}

vector<string> Astronomer::Serialize()
{
    return vector<string>
    {
        this->name,
        this->constellation,
    };
}

void Astronomer::Deserialize(vector<string> tokens)
{
    this->name = tokens[0];
    this->constellation = tokens[1];
}