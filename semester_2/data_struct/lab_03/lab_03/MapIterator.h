#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
    int currentElement;

	MapIterator(const Map& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

class MapIteratorException : public std::exception
{
private:
    const char* message;

public:
    MapIteratorException(const char* message);
    virtual const char* what() const throw();
};
