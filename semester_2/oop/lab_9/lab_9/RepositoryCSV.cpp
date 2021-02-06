#include "RepositoryCSV.h"
#include <algorithm>
#include <sstream>

using namespace std;

vector<Material> RepositoryCSV::loadFromFile()
{
    ifstream file(this->filePath);
    vector<Material> elements;

    string line;
    while (getline(file, line))
    {
        vector<string> lineTokens = Utility::splitString(line, ',');
        Material element(lineTokens);

        elements.push_back(element);
    }

    file.close();

    return elements;
}

void RepositoryCSV::saveToFile(vector<Material> elements)
{
    ofstream file(this->filePath, ofstream::trunc);

    int elementIndex = 0;
    for (auto material : elements)
    {
        file << material.Id() << "," << material.Size() << "," << material.InfectionLevel() << "," << material.MicrofragmentsQuantity() << "," << material.Photograph();

        if (elementIndex < elements.size() - 1)
        {
            file << endl;
        }
        elementIndex++;
    }

    file.close();
}


RepositoryCSV::RepositoryCSV()
{
}


RepositoryCSV::RepositoryCSV(RepositoryCSV const& repository)
{
}


RepositoryCSV::~RepositoryCSV()
{
}
