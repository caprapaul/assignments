#pragma once
#include "SortedIteratedList.h"

#include <exception>

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	ListIterator(const SortedIteratedList& list);

    int currentElementIndex;
    TComp* elements;

    int extractElements(BSTNode* node, int* elements, int index);

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;

    ListIterator(const ListIterator& iterator);
    ~ListIterator();
};

class ListIteratorException : public std::exception
{
private:
    const char* message;

public:
    ListIteratorException(const char* message);
    virtual const char* what() const throw();
};

