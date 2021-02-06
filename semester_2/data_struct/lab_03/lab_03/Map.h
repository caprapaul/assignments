#pragma once
#include <utility>
#include <exception>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111)
class MapIterator;


class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

private:
    TElem* elements;
    int* next;
    int capacity;
    int _size; // number of occupied positions
    int head;
    int firstEmpty;

    void resizeArray(int newCapacity);

public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

    //replaces the value currently mapped to a key k, with value newValue, only if the current value is equal to oldValue.
    //if the current value is not oldValue, or if k is not in the map, nothing is changes.
    void replace(TKey k, TValue oldValue, TValue newValue);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

	// destructor
	~Map();

};

class MapException : public std::exception
{
private:
    const char* message;

public:
    MapException(const char* message);
    virtual const char* what() const throw();
};
