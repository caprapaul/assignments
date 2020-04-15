#pragma once
#include "Vector.h"
#include <exception>

class VectorIteratorException : public std::exception {
private:
    char const* message;

public:
    VectorIteratorException(char const* message);

    virtual char const* what() const throw();
};

template <typename TElement>
class VectorIterator
{
    friend class Vector<TElement>;

private:
    Vector<TElement>& vector;
    int currentElementIndex;

    VectorIterator(Vector<TElement>& vector);

public:
    VectorIterator<TElement>& operator=(VectorIterator<TElement> const& source);

    void First();
    void Next();
    TElement Current() const;
    bool IsValid() const;
};

template<typename TElement>
inline VectorIterator<TElement>::VectorIterator(Vector<TElement>& vector):
    vector(vector)
{
    this->currentElementIndex = 0;
}

template<typename TElement>
inline VectorIterator<TElement>& VectorIterator<TElement>::operator=(VectorIterator<TElement> const & source)
{
    this->currentElementIndex = source.currentElementIndex;
    this->vector = source.vector;

    return *this;
}

template<typename TElement>
inline void VectorIterator<TElement>::First()
{
    this->currentElementIndex = 0;
}

template<typename TElement>
inline void VectorIterator<TElement>::Next()
{
    if (!this->IsValid()) 
    {
        throw  VectorIteratorException("Invalid iterator!");
    }

    this->currentElementIndex++;
}

template<typename TElement>
inline TElement VectorIterator<TElement>::Current() const
{
    if (!this->IsValid())
    {
        throw  VectorIteratorException("Invalid iterator!");
    }

    return this->vector[currentElementIndex];
}

template<typename TElement>
inline bool VectorIterator<TElement>::IsValid() const
{
    return this->currentElementIndex < this->vector.size;
}
