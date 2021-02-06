#pragma once

#include "DLLNode.h"
#include <tuple>
#include <exception>

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix 
{
private:
    int linesCount;
    int columnsCount;
    DLLNode* head;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j);

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    //resizes a Matrix to a given dimension. 
    //If the dimensions are less than the current dimensions, elements from positions no longer existing will disappear. 
    //If the dimensions are greater than the current dimensions, all new elements will be by default NULL_TELEM.
    //throws exception if the new dimensions are zero or negative
    void resize(int newLines, int newCol);
};

class MatrixException : public std::exception
{
private:
    const char* message;

public:
    MatrixException(const char* message);
    virtual const char* what() const throw();
};
