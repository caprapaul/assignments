#include "Matrix.h"
#include <exception>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols)
{
    this->linesCount = nrLines;
    this->columnsCount = nrCols;
}

// Total complexity: Θ(1)
int Matrix::nrLines() const
{
    return this->linesCount;
}

// Total complexity: Θ(1)
int Matrix::nrColumns() const
{
    return this->columnsCount;
}

// Best case: Θ(1)  (When the matrix is empty)
// Worst case: Θ(n) (When the i and j are not found)
// Total complexity: O(n) - where n is the number of non-empty elements
TElem Matrix::element(int i, int j)
{
    if (i < 0 || i >= this->linesCount)
    {
        throw MatrixException("Invalid line.");
    }

    if (j < 0 || j >= this->columnsCount)
    {
        throw MatrixException("Invalid column.");
    }

    DLLNode* currentNode = this->head;

    while (currentNode != nullptr)
    {
        tuple<int, int, TElem> currentInfo = currentNode->info;

        int currentI = get<0>(currentInfo);
        int currentJ = get<1>(currentInfo);
        int currentElem = get<2>(currentInfo);

        if (currentI == i && currentJ == j)
        {
            return currentElem;
        }

        if (currentI == i && currentJ > j)
        {
            break;
        }

        if (currentI > i)
        {
            break;
        }

        currentNode = currentNode->next;
    }

    return NULL_TELEM;
}

// Best case: Θ(1)  (When the matrix is empty)
// Worst case: Θ(n) (When the i and j are not found or higher than existent ones)
// Total complexity: O(n) - where n is the number of non-empty elements
TElem Matrix::modify(int i, int j, TElem e)
{
    if (i < 0 || i >= this->linesCount)
    {
        throw MatrixException("Invalid line.");
    }

    if (j < 0 || j >= this->columnsCount)
    {
        throw MatrixException("Invalid column.");
    }

    TElem foundElement = NULL_TELEM;
    tuple<int, int, TElem> newInfo = make_tuple(i, j, e);

    if (this->head == nullptr)
    {
        DLLNode* newNode = new DLLNode(newInfo, nullptr, nullptr);
        this->head = newNode;

        return NULL_TELEM;
    }

    DLLNode* previousNode = nullptr;
    DLLNode* currentNode = this->head;

    while (currentNode != nullptr)
    {
        tuple<int, int, TElem> currentInfo = currentNode->info;

        int currentI = get<0>(currentInfo);
        int currentJ = get<1>(currentInfo);
        int currentElem = get<2>(currentInfo);

        if (currentI == i && currentJ == j)
        {
            currentNode->info = newInfo;

            return currentElem;
        }

        if (currentI == i && currentJ > j)
        {
            break;
        }

        if (currentI > i)
        {
            break;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    DLLNode* newNode = new DLLNode(newInfo, nullptr, nullptr);

    // If previous node is null it means the while loop broke at the first node(head)
    if (previousNode == nullptr)
    {
        newNode->next = this->head;
        this->head = newNode;
    }
    else
    {
        newNode->next = previousNode->next;
        newNode->prev = previousNode;
        previousNode->next = newNode;
    }

    if (currentNode != nullptr)
    {
        currentNode->prev = newNode;
    }

    return NULL_TELEM;
}

// Best case: Θ(1)  (When the new size is larger than the old one)
// Worst case: Θ(n) (When the new size is smaller than the old one)
// Total complexity: O(n) - where n is the number of non-empty elements
void Matrix::resize(int newLines, int newCol)
{
    if (newLines <= 0)
    {
        throw MatrixException("Invalid lines count.");
    }

    if (newCol <= 0)
    {
        throw MatrixException("Invalid columns count.");
    }

    if (newLines < this->linesCount || newCol < this->columnsCount)
    {
        DLLNode* currentNode = this->head;

        while (currentNode != nullptr)
        {
            tuple<int, int, TElem> currentInfo = currentNode->info;
            DLLNode* nextNode = currentNode->next;

            int currentI = get<0>(currentInfo);
            int currentJ = get<1>(currentInfo);
            int currentElem = get<2>(currentInfo);

            if (currentI >= newLines || currentJ >= newCol)
            {
                if (currentNode == this->head)
                {
                    this->head = currentNode->next;
                }

                if (currentNode->prev != nullptr)
                {
                    currentNode->prev->next = currentNode->next;
                }

                if (currentNode->next != nullptr)
                {
                    currentNode->next->prev = currentNode->prev;
                }

                delete currentNode;
            }

            currentNode = nextNode;
        }
    }

    this->linesCount = newLines;
    this->columnsCount = newCol;
}

MatrixException::MatrixException(const char * message)
{
    this->message = message;
}

const char* MatrixException::what() const throw()
{
    return this->message;
}
