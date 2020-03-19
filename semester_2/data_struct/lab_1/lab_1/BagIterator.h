#include "Bag.h"
#include <exception>

class BagIteratorException : public std::exception
{
    const char* _message;
public:
    BagIteratorException(const char* message);

    virtual const char* what() const throw();
};

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& _bag;
    int _currentElement;
    int _currentOccurences;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
