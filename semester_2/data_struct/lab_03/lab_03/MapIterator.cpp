#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

// Total complexity: Θ(1)
MapIterator::MapIterator(const Map& d) : map(d)
{
    this->currentElement = this->map.head;
}

// Total complexity: Θ(1)
void MapIterator::first() 
{
    this->currentElement = this->map.head;
}

// Total complexity: Θ(1)
void MapIterator::next() 
{
    if (!this->valid())
    {
        throw MapIteratorException("Invalid iterator.");
    }

    this->currentElement = this->map.next[this->currentElement];
}

// Total complexity: Θ(1)
TElem MapIterator::getCurrent()
{
    if (!this->valid())
    {
        throw MapIteratorException("Invalid iterator.");
    }

    return this->map.elements[this->currentElement];
}

// Total complexity: Θ(1)
bool MapIterator::valid() const 
{
    return this->currentElement != -1 && this->currentElement != this->map.firstEmpty;
}

MapIteratorException::MapIteratorException(const char* message)
{
    this->message = message;
}

const char* MapIteratorException::what() const throw()
{
    return this->message;
}
