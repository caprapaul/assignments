#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
    _capacity = 5;
    _length = 0;
    _size = 0;
    _array = new std::pair<TElem, int>[_capacity];
}


void Bag::add(TElem elem) {
    if (_length >= _capacity) {
        resizeArray(_capacity * 2);
    }

    for (int i = 0; i < _length; i++)
    {
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


bool Bag::remove(TElem elem) {
    for (int i = 0; i < _length; i++)
    {
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


bool Bag::search(TElem elem) const {
    for (int i = 0; i < _length; i++)
    {
        std::pair<TElem, int> pair = _array[i];

        if (pair.first == elem) {
            return true;
        }
    }

	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
    for (int i = 0; i < _length; i++)
    {
        std::pair<TElem, int> pair = _array[i];

        if (pair.first == elem) {
            return pair.second;
        }
    }

	return 0; 
}


int Bag::size() const {
    return _size;
}


bool Bag::isEmpty() const {
    return _length == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    delete[] _array;
}


void Bag::resizeArray(int newCapacity) {
    std::pair<TElem, int>* temp = new std::pair<TElem, int>[newCapacity];

    for (int i = 0; i < _length; i++)
    {
        temp[i] = _array[i];
    }

    delete[] _array;
    _array = temp;
    _capacity = newCapacity;
}

void Bag::deleteAt(int index)
{
    for (int i = index; i < _length - 1; i++)
    {
        _array[i] = _array[i + 1];
    }

    _length--;
}

