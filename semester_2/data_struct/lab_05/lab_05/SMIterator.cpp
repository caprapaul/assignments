#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

// Total complexity: Θ(n * log(n))
SMIterator::SMIterator(const SortedMap& m) : map(m)
{
    this->elements = new TElem[this->map._size];
    this->currentElementIndex = 0;
    this->size = m._size;
    
    int currentSize = 0;
    for (int i = 0; i < this->map.capacity; i++)
    {
        TElem currentElement = this->map.elements[i];

        if (currentElement != NULL_TPAIR && currentElement != DELETED_TPAIR)
        {
            int j = currentSize;

            while (j > 0 && !this->map.compare(this->elements[j - 1].first, currentElement.first))
            {
                this->elements[j] = this->elements[j - 1];
                j--;
            }

            this->elements[j] = currentElement;
            currentSize++;
        }
    }
}

// Total complexity: Θ(1)
void SMIterator::first()
{
    this->currentElementIndex = 0;
}

// Total complexity: Θ(1)
void SMIterator::next()
{
    if (!this->valid())
    {
        throw SMIteratorException("Invalid iterator.");
    }

    this->currentElementIndex++;
}

// Total complexity: Θ(1)
bool SMIterator::valid() const
{
    return this->currentElementIndex < this->size;
}

// Total complexity: Θ(1)
TElem SMIterator::getCurrent() const
{
    if (!this->valid())
    {
        throw SMIteratorException("Invalid iterator.");
    }

    return this->elements[this->currentElementIndex];
}

SMIterator::~SMIterator()
{
    delete[] this->elements;
}

SMIteratorException::SMIteratorException(const char* message)
{
    this->message = message;
}

const char* SMIteratorException::what() const throw()
{
    return this->message;
}
