#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;


// Best case: Θ(1)  (no collision)
// Worst case: Θ(n) (n collisions)
// Total complexity: O(n)
void SortedMap::resizeArray(int newCapacity) 
{
    TElem* newElements = new TElem[newCapacity];

    for (int i = 0; i < newCapacity; i++)
    {
        newElements[i] = NULL_TPAIR;
    }

    int oldCapacity = this->capacity;
    int oldSize = this->_size;
    this->capacity = newCapacity;
    this->_size = 0;

    for (int i = 0; i < oldCapacity; i++)
    {
        TElem newElement = this->elements[i];

        if (newElement != NULL_TPAIR && newElement != DELETED_TPAIR)
        {
            TKey key = newElement.first;
            int j = 0;
            int position = this->hash(key, j);
            TElem currentElement = newElements[position];

            while (j < this->capacity && currentElement != NULL_TPAIR && currentElement != DELETED_TPAIR && currentElement.first != key)
            {
                j++;
                position = this->hash(key, j);
                currentElement = newElements[position];
            }

            if (j == this->capacity)
            {
                int newCapacity = this->nextPrime(2 * this->capacity + 1);
                this->capacity = oldCapacity;
                this->_size = oldSize;
                this->resizeArray(newCapacity);

                return;
            }
            else
            {
                newElements[position] = newElement;
                this->_size++;
            }
        }
    }

    delete[] this->elements;
    this->elements = newElements;
}

bool SortedMap::isPrime(int x) const
{
    for (int i = 3; i * i < x; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }

    return true;
}

int SortedMap::nextPrime(int x) const
{
    int next = x + 2;

    while (!isPrime(next))
    {
        next += 2;
    }

    return next;
}

// Total complexity: Θ(1)
int SortedMap::hash1(TKey key) const
{
    int result = key % this->capacity;
    return result > 0 ? result : -result;
}

// Total complexity: Θ(1)
int SortedMap::hash2(TKey key) const
{
    int result = 1 + (key % (this->capacity - 1));
    return result > 0 ? result : -result;
}

// Total complexity: Θ(1)
int SortedMap::hash(TKey key, int probeNumber) const
{
    return (hash1(key) + probeNumber * hash2(key)) % this->capacity;
}

// Total complexity: Θ(n) - n capacity
SortedMap::SortedMap(Relation r) 
{
    this->capacity = 7;
    this->_size = 0;
    this->elements = new TElem[this->capacity];

    for (int i = 0; i < this->capacity; i++)
    {
        this->elements[i] = NULL_TPAIR;
    }

    this->compare = r;
}

// Best case: Θ(1)  (no collision)
// Worst case: Θ(n) (n collisions)
// Total complexity: O(n)
TValue SortedMap::add(TKey k, TValue v)
{
    int i = 0;
    int position = this->hash(k, i);
    TElem currentElement = this->elements[position];

    while (i < this->capacity && currentElement != NULL_TPAIR && currentElement != DELETED_TPAIR && currentElement.first != k)
    {
        i++;
        position = this->hash(k, i);
        currentElement = this->elements[position];
    }

    if (i == this->capacity)
    {
        int newCapacity = this->nextPrime(2 * this->capacity + 1);
        this->resizeArray(newCapacity);

        return add(k, v);
    }
    else
    {
        this->elements[position] = TElem(k, v);

        if (currentElement.first == k)
        {
            return currentElement.second;
        }
        else
        {
            this->_size++;
            return NULL_TVALUE;
        }
    }
}


// Best case: Θ(1)  (no collisions)
// Worst case: Θ(n) (n colissions)
// Total complexity: O(n)
TValue SortedMap::search(TKey k) const 
{
    int i = 0;
    int position = this->hash(k, i);
    TElem currentElement = this->elements[position];

    while (i < this->capacity && currentElement != NULL_TPAIR && currentElement.first != k)
    {
        i++;
        position = this->hash(k, i);
        currentElement = this->elements[position];
    }

    if (currentElement.first == k)
    {
        return currentElement.second;
    }
    else
    {
        return NULL_TVALUE;
    }
}

// Best case: Θ(1)  (no collisions)
// Worst case: Θ(n) (n colissions)
// Total complexity: O(n)
TValue SortedMap::remove(TKey k)
{
    int i = 0;
    int position = this->hash(k, i);
    TElem currentElement = this->elements[position];

    while (i < this->capacity && currentElement != NULL_TPAIR && currentElement.first != k)
    {
        i++;
        position = this->hash(k, i);
        currentElement = this->elements[position];
    }

    if (currentElement.first == k)
    {
        this->elements[position] = DELETED_TPAIR;
        this->_size--;

        return currentElement.second;
    }
    else
    {
        return NULL_TVALUE;
    }

}

// Total complexity: Θ(1)
int SortedMap::size() const 
{
    return this->_size;
}

// Total complexity: Θ(1)
bool SortedMap::isEmpty() const
{
    return this->_size == 0;
}

// Total complexity: Θ(n * log(n))
SMIterator SortedMap::iterator() const 
{
	return SMIterator(*this);
}

// Total complexity: Θ(n * n * log(n))
void SortedMap::filter(Condition cond)
{
    SMIterator iterator(*this);
    iterator.first();

    while (iterator.valid())
    {
        TKey key = iterator.getCurrent().first;

        if (!cond(key))
        {
            this->remove(key);
        }

        iterator.next();
    }
}

SortedMap::~SortedMap() 
{
    delete[] this->elements;
}
