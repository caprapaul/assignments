#pragma once

#include "Vector.h"
#include "VectorIterator.h"
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
    Vector<TElement> elements;
    VectorIterator<TElement> elementsIterator;

public:
    Repository();
    Repository(Vector<TElement> elements);
    Repository(const Repository<TElement> &source);
    ~Repository();

    void Add(TElement element);
    template<typename TCondition>
    void RemoveIf(TCondition condition);
    template<typename TCondition>
    Vector<TElement> FindIf(TCondition condition);
    template<typename TCondition>
    TElement FindFirst(TCondition condition);
    template<typename TCondition>
    void UpdateFirst(TCondition condition, TElement newElement);
    template<typename TCondition>
    void RemoveFirst(TCondition condition);
    Vector<TElement> GetAll();
    template<typename TCondition>
    TElement GetNext(TCondition condition);
};

template <typename TElement>
Repository<TElement>::Repository(): 
    elementsIterator(elements.Iterator())
{
    this->elementsIterator = this->elements.Iterator();
}

template <typename TElement>
inline Repository<TElement>::Repository(Vector<TElement> elements)
{
    this->elements = elements;
    this->elementsIterator = this->elements.Iterator();
}

template <typename TElement>
inline Repository<TElement>::Repository(const Repository<TElement> &source)
{
    this->elements = source.elements;
    this->elementsIterator = this->elements.Iterator();
}

template <typename TElement>
inline Repository<TElement>::~Repository()
{

}

template<typename TElement>
inline void Repository<TElement>::Add(TElement element)
{
    this->elements.Push(element);
}

template<typename TElement>
inline Vector<TElement> Repository<TElement>::GetAll()
{
    return this->elements;
}

template<typename TElement>
template<typename TCondition>
inline void Repository<TElement>::RemoveIf(TCondition condition)
{
    for (int i = 0; i < this->elements.Size(); i++)
    {
        TElement currentElement = this->elements[i];

        if (condition(currentElement) == true)
        {
            this->elements.Remove(i);
        }
    }
}

template<typename TElement>
template<typename TCondition>
inline Vector<TElement> Repository<TElement>::FindIf(TCondition condition)
{
    Vector<TElement> found;

    for (int i = 0; i < this->elements.Size(); i++)
    {
        TElement currentElement = this->elements[i];

        if (condition(currentElement))
        {
            found.Push(currentElement);
        }
    }

    return found;
}

template<typename TElement>
template<typename TCondition>
inline TElement Repository<TElement>::FindFirst(TCondition condition)
{
    for (int i = 0; i < this->elements.Size(); i++)
    {
        TElement currentElement = this->elements[i];

        if (condition(currentElement))
        {
            return currentElement;
        }
    }

    throw RepositoryException("No element meets the condition.");
}

template<typename TElement>
template<typename TCondition>
inline void Repository<TElement>::UpdateFirst(TCondition condition, TElement newElement)
{
    for (int i = 0; i < this->elements.Size(); i++)
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
    for (int i = 0; i < this->elements.Size(); i++)
    {
        TElement currentElement = this->elements[i];
        bool result = condition(currentElement);
        if (result== true)
        {
            this->elements.Remove(i);
            return;
        }
    }
}

template<typename TElement>
template<typename TCondition>
 TElement Repository<TElement>::GetNext(TCondition condition)
{
    if (!this->elementsIterator.IsValid())
    {
        this->elementsIterator.First();
    }

    while (this->elementsIterator.IsValid())
    {
        TElement currentElement = this->elementsIterator.Current();
        this->elementsIterator.Next();

        if (condition(currentElement))
        {
            return currentElement;
        }

    }

    throw RepositoryException("No element meets the condition.");
}
