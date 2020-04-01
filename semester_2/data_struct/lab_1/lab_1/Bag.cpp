#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

BagException::BagException(const char* message) {
    _message = message;
}

const char* BagException::what() const throw() {
    return _message;
}

Bag::Bag() {
    _length = 0;
    _size = 0;
    _capacity = 5;
    _array = new std::pair<TElem, int>[_capacity];
}

// Best case: Θ(1)  (When the element is found on the first position)
// Worst case: Θ(n) (When the element is not found)
// Total complexity: O(n)
void Bag::add(TElem elem) {
    if (_length >= _capacity) {
        resizeArray(_capacity * 2);
    }

    for (int i = 0; i < _length; i++) {
        std::pair<TElem, int> pair = _array[i];

        if (pair.first == elem) {
            pair.second++;
            _array[i] = pair;
            _size++;

            return;
        }
    }

    std::pair<TElem, int> pair(elem, 1);
    _array[_length] = pair;
    _length++;
    _size++;
}

// Best case: Θ(1)  (When the element is found on the first position 
//                  and the frequency is greater than 1)
// Worst case: Θ(n) (When the element is found on the last position 
//                  or the frequency is 1)
// Total complexity: O(n)
bool Bag::remove(TElem elem) {
    for (int i = 0; i < _length; i++) {
        std::pair<TElem, int> pair = _array[i];

        if (pair.first == elem) {
            pair.second--;

            if (pair.second <= 0) {
                deleteAt(i);
            }
            else {
                _array[i] = pair;
            }

            _size--;

            return true;
        }
    }

	return false; 
}

// Best case: Θ(1)  (When the element is found on the first position)
// Worst case: Θ(n) (When the element is not found or found on the last position)
// Total complexity: O(n)
bool Bag::search(TElem elem) const {
    for (int i = 0; i < _length; i++) {
        std::pair<TElem, int> pair = _array[i];

        if (pair.first == elem) {
            return true;
        }
    }

	return false; 
}

// Best case: Θ(1)  (When index is _length - 1)
// Worst case: Θ(n) (When index is 0)
// Total complexity: O(n)
int Bag::nrOccurrences(TElem elem) const {
    for (int i = 0; i < _length; i++) {
        std::pair<TElem, int> pair = _array[i];

        if (pair.first == elem) {
            return pair.second;
        }
    }

	return 0; 
}

// Total complexity: Θ(1)
int Bag::size() const {
    return _size;
}

// Total complexity: Θ(1)
bool Bag::isEmpty() const {
    return _length == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

// Best case: Θ(1)  (When the element is found on the first position)
// Worst case: Θ(n) (When the element is not found)
// Total complexity: O(n)
void Bag::addOccurrences(int nr, TElem elem) {
    if (nr < 0) {
        throw BagException("Invalid nr: cannot be negative.");
    }

    if (_length >= _capacity) {
        resizeArray(_capacity * 2);
    }

    for (int i = 0; i < _length; i++) {
        std::pair<TElem, int> pair = _array[i];

        if (pair.first == elem) {
            pair.second += nr;
            _array[i] = pair;
            _size += nr;

            return;
        }
    }

    std::pair<TElem, int> pair(elem, nr);
    _array[_length] = pair;
    _length++;
    _size += nr;
}


Bag::~Bag() {
    delete[] _array;
}

// Total complexity: Θ(n)
void Bag::resizeArray(int newCapacity) {
    std::pair<TElem, int>* temp = new std::pair<TElem, int>[newCapacity];

    for (int i = 0; i < _length; i++) {
        temp[i] = _array[i];
    }

    delete[] _array;
    _array = temp;
    _capacity = newCapacity;
}

// Best case: Θ(1)  (When index is _length - 1)
// Worst case: Θ(n) (When index is 0)
// Total complexity: O(n)
void Bag::deleteAt(int index)
{
    for (int i = index; i < _length - 1; i++) {
        _array[i] = _array[i + 1];
    }

    _length--;
}

