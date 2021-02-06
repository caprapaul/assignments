#pragma once
#include "SortedMap.h"

#include <exception>

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

    TElem* elements;
    int currentElementIndex;
    int size;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;

    ~SMIterator();
};

class SMIteratorException : public std::exception
{
private:
    const char* message;

public:
    SMIteratorException(const char* message);
    virtual const char* what() const throw();
};
