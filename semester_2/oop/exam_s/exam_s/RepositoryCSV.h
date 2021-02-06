#pragma once
#include "RepositoryFile.h"
#include "Utility.h"
#include <fstream>
#include <vector>

template <typename TElement>
class RepositoryCSV : public RepositoryFile<TElement>
{
private:
    std::vector<TElement> loadFromFile();
    void saveToFile(std::vector<TElement> elements);

public:
    RepositoryCSV();
    RepositoryCSV(RepositoryCSV const& repository);
    ~RepositoryCSV();

};

template <typename TElement>
std::vector<TElement> RepositoryCSV<TElement>::loadFromFile()
{
    std::ifstream file(this->filePath);
    std::vector<TElement> elements;

    std::string line;
    while (std::getline(file, line))
    {
        vector<string> lineTokens = Utility::splitString(line, ',');
        TElement element;
        element.Deserialize(lineTokens);

        elements.push_back(element);
    }

    file.close();

    return elements;
}

template <typename TElement>
void RepositoryCSV<TElement>::saveToFile(std::vector<TElement> elements)
{
    std::ofstream file(this->filePath, std::ofstream::trunc);

    int elementIndex = 0;
    for (auto element : elements)
    {
        std::vector<std::string> tokens = element.Serialize();

        for (size_t i = 0; i < tokens.size(); i++)
        {
            file << tokens[i];

            if (i < tokens.size() - 1)
            {
                file << ",";
            }
        }

        if (elementIndex < elements.size() - 1)
        {
            file << endl;
        }
        elementIndex++;
    }

    file.close();
}

template <typename TElement>
RepositoryCSV<TElement>::RepositoryCSV()
{
}

template <typename TElement>
RepositoryCSV<TElement>::RepositoryCSV(RepositoryCSV const& repository)
{
}

template <typename TElement>
RepositoryCSV<TElement>::~RepositoryCSV()
{
}
