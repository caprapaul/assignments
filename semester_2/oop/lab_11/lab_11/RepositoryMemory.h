#pragma once

#include "Repository.h"
#include <algorithm>

template <typename TElement>
class RepositoryMemory: public Repository<TElement>
{
private:
    std::vector<TElement> elements;
    int currentElementIndex;

public:
    RepositoryMemory();
    RepositoryMemory(std::vector<TElement> elements);
    RepositoryMemory(RepositoryMemory<TElement> const& source);
    ~RepositoryMemory();

    void Add(TElement element);
    void RemoveIf(std::function<bool(TElement)> condition);
    std::vector<TElement> FindIf(std::function<bool(TElement)> condition);
    TElement FindFirst(std::function<bool(TElement)> condition);
    void UpdateFirst(std::function<bool(TElement)> condition, TElement newElement);
    void RemoveFirst(std::function<bool(TElement)> condition);
    std::vector<TElement> GetAll();
    TElement GetNext(std::function<bool(TElement)> condition);
    void Clear();
};

template <typename TElement>
RepositoryMemory<TElement>::RepositoryMemory()
{
    this->currentElementIndex = 0;
}

template <typename TElement>
inline RepositoryMemory<TElement>::RepositoryMemory(std::vector<TElement> elements)
{
    this->elements = elements;
    this->currentElementIndex = 0;
}

template <typename TElement>
inline RepositoryMemory<TElement>::RepositoryMemory(const RepositoryMemory<TElement> &source)
{
    this->elements = source.elements;
    this->currentElementIndex = source.currentElementIndex;
}

template <typename TElement>
inline RepositoryMemory<TElement>::~RepositoryMemory()
{

}

template<typename TElement>
inline void RepositoryMemory<TElement>::Add(TElement element)
{
    this->elements.push_back(element);
}

template<typename TElement>
inline std::vector<TElement> RepositoryMemory<TElement>::GetAll()
{
    return this->elements;
}

template<typename TElement>
inline void RepositoryMemory<TElement>::RemoveIf(std::function<bool(TElement)> condition)
{
    this->elements.erase(
        std::remove_if(this->elements.begin(), this->elements.end(), condition),
        this->elements.end());
}

template<typename TElement>
inline std::vector<TElement> RepositoryMemory<TElement>::FindIf(std::function<bool(TElement)> condition)
{
    std::vector<TElement> found;
    typename std::vector<TElement>::iterator foundIterator = this->elements.begin();

    while (foundIterator != this->elements.end())
    {
        foundIterator = std::find_if(foundIterator, this->elements.end(), condition);

        if (foundIterator != this->elements.end())
        {
            found.push_back(*foundIterator);
            foundIterator++;
        }
    }

    return found;
}

template<typename TElement>
inline TElement RepositoryMemory<TElement>::FindFirst(std::function<bool(TElement)> condition)
{
    typename std::vector<TElement>::iterator foundIterator = std::find_if(this->elements.begin(), this->elements.end(), condition);
    if (foundIterator == this->elements.end())
    {
        throw RepositoryException("No element meets the condition.");
    }

    return *foundIterator;
}

template<typename TElement>
inline void RepositoryMemory<TElement>::UpdateFirst(std::function<bool(TElement)> condition, TElement newElement)
{
    for (int i = 0; i < this->elements.size(); i++)
    {
        TElement currentElement = this->elements[i];

        if (condition(currentElement))
        {
            this->elements[i] = newElement;
            return;
        }
    }
}

template<typename TElement>
inline void RepositoryMemory<TElement>::RemoveFirst(std::function<bool(TElement)> condition)
{
    typename std::vector<TElement>::iterator foundIterator = std::find_if(this->elements.begin(), this->elements.end(), condition);

    if (foundIterator != this->elements.end())
    {
        this->elements.erase(foundIterator);
    }
}

template<typename TElement>
 TElement RepositoryMemory<TElement>::GetNext(std::function<bool(TElement)> condition)
{
     if (this->currentElementIndex == this->elements.size())
     {
         this->currentElementIndex = 0;
     }

     while (this->currentElementIndex < this->elements.size())
     {
         TElement currentElement = this->elements[this->currentElementIndex];
         this->currentElementIndex++;

         if (condition(currentElement))
         {
             return currentElement;
         }
     }

     throw RepositoryException("No element meets the condition.");
 }

 template<typename TElement>
 inline void RepositoryMemory<TElement>::Clear()
 {
     this->elements = std::vector<TElement>();
 }
