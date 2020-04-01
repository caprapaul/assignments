#pragma once
#include <utility>
#include <exception>
//DO NOT INCLUDE BAGITERATOR

class BagException : public std::exception {

private:
    const char* _message;

public:
    BagException(const char* message);

    virtual const char* what() const throw();
};

//DO NOT CHANGE THIS PART
#define NULL_TELEM -11111;
typedef int TElem;
class BagIterator; 
class Bag {

private:
    std::pair<TElem, int>* _array;
    // The number of unique elements.
    int _length;
    // The total number of elements.
    int _size;
    // The number of unique elements the bag can hold before resizing.
    int _capacity;

    void resizeArray(int newCapacity);
    void deleteAt(int index);

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

    //adds nr occurrences of elem in the Bag.
    //throws an exception if nr is negative
    void addOccurrences(int nr, TElem elem);

	//destructor
	~Bag();
};