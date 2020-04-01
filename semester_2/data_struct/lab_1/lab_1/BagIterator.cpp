#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

BagIteratorException::BagIteratorException(const char* message) {
    _message = message;
}

const char* BagIteratorException::what() const throw() {
    return _message;
}


BagIterator::BagIterator(const Bag& c): _bag(c){
    _currentElement = 0;
    _currentOccurences = 1;
}

// Total complexity: Θ(1)
void BagIterator::first() {
    _currentElement = 0;
    _currentOccurences = 1;
}

// Total complexity: Θ(1)
void BagIterator::next() {
    if (!valid()) {
        throw  BagIteratorException("Invalid iterator!");
    }

    if (_currentOccurences >= _bag._array[_currentElement].second) {
        _currentElement++;
        _currentOccurences = 1;
    }
    else {
        _currentOccurences++;
    }
}

// Total complexity: Θ(1)
bool BagIterator::valid() const {
	return _currentElement < _bag._length;
}

// Total complexity: Θ(1)
TElem BagIterator::getCurrent() const
{
    if (!valid()) {
        throw  BagIteratorException("Invalid iterator!");
    }

    return _bag._array[_currentElement].first;
}
