#pragma once
#include "Repository.h"
#include <fstream>

template <typename TElement>
class RepositoryText : public Repository<TElement>
{
public:
    RepositoryText();
    RepositoryText(Repository<TElement>const& repository);
    ~RepositoryText();

    void LoadFromFile(std::string filePath);
    void SaveToFile(std::string filePath);
};

template<typename TElement>
inline RepositoryText<TElement>::RepositoryText()
{
}

template<typename TElement>
inline RepositoryText<TElement>::RepositoryText(Repository<TElement> const& repository)
    :Repository<TElement>(repository)
{
}

template<typename TElement>
inline RepositoryText<TElement>::~RepositoryText()
{
}

template<typename TElement>
inline void RepositoryText<TElement>::LoadFromFile(std::string filePath)
{
    std::ifstream file(filePath);
    TElement element;

    while (file >> element)
    {
        Repository<TElement>::Add(element);
    }

    file.close();
}

template<typename TElement>
inline void RepositoryText<TElement>::SaveToFile(std::string filePath)
{
    std::ofstream file(filePath);

    int elementIndex = 0;
    for (auto element : this->elements)
    {
        file << element;

        if (elementIndex < this->elements.size() - 1)
        {
            file << std::endl;
        }
        elementIndex++;
    }

    file.close();
}
