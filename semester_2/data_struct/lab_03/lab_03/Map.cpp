#include "Map.h"
#include "MapIterator.h"

using namespace std;

// Total complexity: Θ(n) - where n is the new capacity
void Map::resizeArray(int newCapacity) {
    TElem* newElements = new TElem[newCapacity];

    for (int i = 0; i < this->_size; i++) 
    {
        newElements[i] = this->elements[i];
    }

    delete[] this->elements;
    this->elements = newElements;

    this->firstEmpty = this->capacity;

    int* newNext = new int[newCapacity];

    for (int i = 0; i < this->capacity - 1; i++)
    {
        newNext[i] = this->next[i];
    }

    for (int i = this->capacity - 1; i < newCapacity; i++)
    {
        newNext[i] = i + 1;
    }

    newNext[newCapacity - 1] = -1;

    delete[] this->next;
    this->next = newNext;
    this->capacity = newCapacity;
}

// Total complexity: Θ(n) - where n is the initial capacity
Map::Map() 
{
    this->capacity = 2;
    this->elements = new TElem[this->capacity];
    this->next = new int[this->capacity];
    this->head = -1;

    for (int i = 0; i < this->capacity; i++)
    {
        this->next[i] = i + 1;
    }

    this->next[this->capacity - 1] = -1;
    this->firstEmpty = 0;
}

Map::~Map() 
{
    delete[] this->elements;
    delete[] this->next;
}

// Best case: Θ(1)  (When the map is empty)
// Worst case: Θ(n) (When the key doesn't exist)
// Total complexity: O(n) - where n is the current size
TValue Map::add(TKey c, TValue v)
{
    if (this->firstEmpty == -1)
    {
        this->resizeArray(this->capacity * 2);
    }

    if (this->isEmpty())
    {
        TElem newElement = TElem(c, v);
        this->elements[this->firstEmpty] = newElement;
        this->head = this->firstEmpty;
        this->firstEmpty = this->next[this->firstEmpty];
        this->_size++;

        return NULL_TVALUE;
    }

    int currentNode = this->head;

    while (currentNode != -1 && currentNode != firstEmpty && this->elements[currentNode].first != c)
    {
        currentNode = this->next[currentNode];
    }

    TElem newElement = TElem(c, v);

    // Key already exists
    if (currentNode != -1 && currentNode != firstEmpty)
    {
        TValue oldValue = this->elements[currentNode].second;
        this->elements[currentNode] = newElement;

        return oldValue;
    }
    
    // Key does not exist
    this->elements[this->firstEmpty] = newElement;
    this->firstEmpty = this->next[this->firstEmpty];
    this->_size++;

    return NULL_TVALUE;
}

// Best case: Θ(1)  (When the map is empty)
// Worst case: Θ(n) (When the key doesn't exist)
// Total complexity: O(n) - where n is the current size
TValue Map::search(TKey c) const
{
    if (this->isEmpty())
    {
        return NULL_TVALUE;
    }

    int currentNode = this->head;

    while (currentNode != -1 && currentNode != firstEmpty && this->elements[currentNode].first != c)
    {
        currentNode = this->next[currentNode];
    }

    // Key exists
    if (currentNode != -1 && currentNode != firstEmpty)
    {
        return this->elements[currentNode].second;
    }

    return NULL_TVALUE;
}

// Best case: Θ(1)  (When the map is empty)
// Worst case: Θ(n) (When the key doesn't exist)
// Total complexity: O(n) - where n is the current size
TValue Map::remove(TKey c)
{
    if (this->isEmpty())
    {
        return NULL_TVALUE;
    }

    int currentNode = this->head;
    int previousNode = -1;

    // Iterate the list until we reach the end or the key is equal to c
    while (currentNode != -1 && currentNode != firstEmpty && this->elements[currentNode].first != c)
    {
        previousNode = currentNode;
        currentNode = this->next[currentNode];
    }

    // Key exists
    if (currentNode != -1 && currentNode != firstEmpty)
    {
        if (currentNode == this->head)
        {
            this->head = this->next[this->head];
        }
        else
        {
            this->next[previousNode] = this->next[currentNode];
        }

        // Add the current node after the first empty node
        this->next[currentNode] = this->next[this->firstEmpty];
        this->next[firstEmpty] = currentNode;
        this->_size--;

        return this->elements[currentNode].second;
    }

    return NULL_TVALUE;
}

// Best case: Θ(1)  (When the map is empty)
// Worst case: Θ(n) (When the key doesn't exist)
// Total complexity: O(n) - where n is the current size
void Map::replace(TKey k, TValue oldValue, TValue newValue)
{
    if (this->isEmpty())
    {
        return;
    }

    int currentNode = this->head;

    while (currentNode != -1 && currentNode != firstEmpty)
    {
        TElem currentElement = this->elements[currentNode];

        if (currentElement.first == k && currentElement.second == oldValue)
        {
            break;
        }

        currentNode = this->next[currentNode];
    }

    // Key exists
    if (currentNode != -1 && currentNode != firstEmpty)
    {
        TElem newElement = TElem(k, newValue);
        this->elements[currentNode] = newElement;
    }
}

// Total complexity: Θ(1)
int Map::size() const 
{
    return this->_size;
}

// Total complexity: Θ(1)
bool Map::isEmpty() const 
{
    return this->_size == 0;
}

// Total complexity: Θ(1)
MapIterator Map::iterator() const
{
    return MapIterator(*this);
}

MapException::MapException(const char * message)
{
    this->message = message;
}

const char* MapException::what() const throw()
{
    return this->message;
}
