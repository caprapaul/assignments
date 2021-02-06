#pragma once

#include <vector>
#include <algorithm>

class RepositoryException : public std::exception {
private:
    char const* message;

public:
    RepositoryException(char const* message);

    virtual char const* what() const throw();
};

template <typename TElement>
class Repository
{
protected:
    std::vector<TElement> elements;
    int currentElementIndex;

public:
    Repository();
    Repository(std::vector<TElement> elements);
    Repository(Repository<TElement> const& source);
    ~Repository();

    void Add(TElement element);
    template<typename TCondition>
    void RemoveIf(TCondition condition);
    template<typename TCondition>
    std::vector<TElement> FindIf(TCondition condition);
    template<typename TCondition>
    TElement FindFirst(TCondition condition);
    template<typename TCondition>
    void UpdateFirst(TCondition condition, TElement newElement);
    template<typename TCondition>
    void RemoveFirst(TCondition condition);
    std::vector<TElement> GetAll();
    template<typename TCondition>
    TElement GetNext(TCondition condition);
};

template <typename TElement>
Repository<TElement>::Repository()
{
    this->currentElementIndex = 0;
}

template <typename TElement>
inline Repository<TElement>::Repository(std::vector<TElement> elements)
{
    this->elements = elements;
    this->currentElementIndex = 0;
}

template <typename TElement>
inline Repository<TElement>::Repository(const Repository<TElement> &source)
{
    this->elements = source.elements;
    this->currentElementIndex = source.currentElementIndex;
}

template <typename TElement>
inline Repository<TElement>::~Repository()
{

}

template<typename TElement>
inline void Repository<TElement>::Add(TElement element)
{
    this->elements.push_back(element);
}

template<typename TElement>
inline std::vector<TElement> Repository<TElement>::GetAll()
{
    return this->elements;
}

template<typename TElement>
template<typename TCondition>
inline void Repository<TElement>::RemoveIf(TCondition condition)
{
    this->elements.erase(
        std::remove_if(this->elements.begin(), this->elements.end(), condition),
        this->elements.end());
}

template<typename TElement>
template<typename TCondition>
inline std::vector<TElement> Repository<TElement>::FindIf(TCondition condition)
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
template<typename TCondition>
inline TElement Repository<TElement>::FindFirst(TCondition condition)
{
    typename std::vector<TElement>::iterator foundIterator = std::find_if(this->elements.begin(), this->elements.end(), condition);
    if (foundIterator == this->elements.end())
    {
        throw RepositoryException("No element meets the condition.");
    }

    return *foundIterator;
}

template<typename TElement>
template<typename TCondition>
inline void Repository<TElement>::UpdateFirst(TCondition condition, TElement newElement)
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
template<typename TCondition>
inline void Repository<TElement>::RemoveFirst(TCondition condition)
{
    typename std::vector<TElement>::iterator foundIterator = std::find_if(this->elements.begin(), this->elements.end(), condition);

    if (foundIterator != this->elements.end())
    {
        this->elements.erase(foundIterator);
    }
}

template<typename TElement>
template<typename TCondition>
 TElement Repository<TElement>::GetNext(TCondition condition)
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
