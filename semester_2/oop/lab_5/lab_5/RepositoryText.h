#pragma once
#include "Repository.h"
#include <fstream>
#include <algorithm>

template <typename TElement>
class RepositoryText : public Repository<TElement>
{
private:
    std::string filePath;
    int currentElementIndex = 0;

    std::vector<TElement> loadFromFile();
    void saveToFile(std::vector<TElement> elements);

public:
    RepositoryText();
    RepositoryText(RepositoryText<TElement>const& repository);
    ~RepositoryText();

    void Add(TElement element);
    void RemoveIf(std::function<bool(TElement)> condition);

    std::vector<TElement> FindIf(std::function<bool(TElement)> condition);
    TElement FindFirst(std::function<bool(TElement)> condition);
    void UpdateFirst(std::function<bool(TElement)> condition, TElement newElement);
    void RemoveFirst(std::function<bool(TElement)> condition);

    std::vector<TElement> GetAll();
    TElement GetNext(std::function<bool(TElement)> condition);

    void SetFile(std::string filePath);
    void Clear();
};

template<typename TElement>
inline std::vector<TElement> RepositoryText<TElement>::loadFromFile()
{
    std::ifstream file(filePath);
    std::vector<TElement> elements;
    TElement element;

    while (file >> element)
    {
        elements.push_back(element);
    }

    file.close();

    return elements;
}

template<typename TElement>
inline void RepositoryText<TElement>::saveToFile(std::vector<TElement> elements)
{
    std::ofstream file(filePath, std::ofstream::trunc);

    int elementIndex = 0;
    for (auto element : elements)
    {
        file << element;

        if (elementIndex < elements.size() - 1)
        {
            file << std::endl;
        }
        elementIndex++;
    }

    file.close();
}

template<typename TElement>
inline RepositoryText<TElement>::RepositoryText()
{
}

template<typename TElement>
inline RepositoryText<TElement>::RepositoryText(RepositoryText<TElement> const& repository)
{
}

template<typename TElement>
inline RepositoryText<TElement>::~RepositoryText()
{
}

template<typename TElement>
inline void RepositoryText<TElement>::Add(TElement element)
{
    std::vector<TElement> elements = this->loadFromFile();

    elements.push_back(element);

    this->saveToFile(elements);
}

template<typename TElement>
inline std::vector<TElement> RepositoryText<TElement>::GetAll()
{
    return this->loadFromFile();
}

template<typename TElement>
inline void RepositoryText<TElement>::RemoveIf(std::function<bool(TElement)> condition)
{
    std::vector<TElement> elements = this->loadFromFile();

    elements.erase(
        std::remove_if(elements.begin(), elements.end(), condition),
        elements.end());

    this->saveToFile(elements);
}

template<typename TElement>
inline std::vector<TElement> RepositoryText<TElement>::FindIf(std::function<bool(TElement)> condition)
{
    std::vector<TElement> elements = this->loadFromFile();

    std::vector<TElement> found;
    typename std::vector<TElement>::iterator foundIterator = elements.begin();

    while (foundIterator != elements.end())
    {
        foundIterator = std::find_if(foundIterator, elements.end(), condition);

        if (foundIterator != elements.end())
        {
            found.push_back(*foundIterator);
            foundIterator++;
        }
    }

    return found;
}

template<typename TElement>
inline TElement RepositoryText<TElement>::FindFirst(std::function<bool(TElement)> condition)
{
    std::vector<TElement> elements = this->loadFromFile();

    typename std::vector<TElement>::iterator foundIterator = std::find_if(elements.begin(), elements.end(), condition);
    if (foundIterator == elements.end())
    {
        throw RepositoryException("No element meets the condition.");
    }

    return *foundIterator;
}

template<typename TElement>
inline void RepositoryText<TElement>::UpdateFirst(std::function<bool(TElement)> condition, TElement newElement)
{
    std::vector<TElement> elements = this->loadFromFile();

    for (int i = 0; i < elements.size(); i++)
    {
        TElement currentElement = elements[i];

        if (condition(currentElement))
        {
            elements[i] = newElement;
            break;
        }
    }

    this->saveToFile(elements);
}

template<typename TElement>
inline void RepositoryText<TElement>::RemoveFirst(std::function<bool(TElement)> condition)
{
    std::vector<TElement> elements = this->loadFromFile();

    typename std::vector<TElement>::iterator foundIterator = std::find_if(elements.begin(), elements.end(), condition);

    if (foundIterator != elements.end())
    {
        elements.erase(foundIterator);
    }

    this->saveToFile(elements);
}

template<typename TElement>
inline TElement RepositoryText<TElement>::GetNext(std::function<bool(TElement)> condition)
{
    std::vector<TElement> elements = this->loadFromFile();

    if (this->currentElementIndex == elements.size())
    {
        this->currentElementIndex = 0;
    }

    while (this->currentElementIndex < elements.size())
    {
        TElement currentElement = elements[this->currentElementIndex];
        this->currentElementIndex++;

        if (condition(currentElement))
        {
            return currentElement;
        }
    }

    throw RepositoryException("No element meets the condition.");
}

template<typename TElement>
inline void RepositoryText<TElement>::SetFile(std::string filePath)
{
    this->filePath = filePath;
}

template<typename TElement>
inline void RepositoryText<TElement>::Clear()
{
    std::vector<TElement> elements;
    this->saveToFile(elements);
}
