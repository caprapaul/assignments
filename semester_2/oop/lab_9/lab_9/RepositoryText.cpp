#include "RepositoryText.h"

using namespace std;

vector<Material> RepositoryText::loadFromFile()
{
    ifstream file(this->filePath);
    vector<Material> elements;
    Material element;

    while (file >> element)
    {
        elements.push_back(element);
    }

    file.close();

    return elements;
}

void RepositoryText::saveToFile(vector<Material> elements)
{
    ofstream file(this->filePath, ofstream::trunc);

    int elementIndex = 0;
    for (auto element : elements)
    {
        file << element;

        if (elementIndex < elements.size() - 1)
        {
            file << endl;
        }
        elementIndex++;
    }

    file.close();
}


RepositoryText::RepositoryText()
{
}


RepositoryText::RepositoryText(RepositoryText const& repository)
{
}


RepositoryText::~RepositoryText()
{
}
