#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

// Total complexity: Θ(n)
int ListIterator::extractElements(BSTNode* node, int* elements, int index) 
{
    if (node == nullptr)
    {
        return index;
    }

    if (node->left != nullptr) 
    {
        index = extractElements(node->left, elements, index);
    }

    if (node->isRemoved)
    {
        return index;
    }

    elements[index] = node->info;

    if (node->right != nullptr)
    {
        index = extractElements(node->right, elements, index);
    }

    return index + 1;
}

ListIterator::ListIterator(const SortedIteratedList& list) : list(list)
{
    this->elements = new TComp[list._size];
    this->extractElements(list.root, this->elements, 0);
    this->currentElementIndex = 0;
}

ListIterator::ListIterator(const ListIterator& iterator) : list(iterator.list)
{
    this->elements = new TComp[this->list._size];
    this->extractElements(this->list.root, this->elements, 0);
    this->currentElementIndex = 0;
}

// Total complexity: Θ(1)
void ListIterator::first()
{
    this->currentElementIndex = 0;
}

// Total complexity: Θ(1)
void ListIterator::next()
{
    if (!this->valid())
    {
        throw ListIteratorException("Invalid iterator.");
    }

    this->currentElementIndex++;
}

bool ListIterator::valid() const
{
    return this->currentElementIndex < this->list._size;
}

TComp ListIterator::getCurrent() const
{
    if (!this->valid())
    {
        throw ListIteratorException("Invalid iterator.");
    }

    return this->elements[this->currentElementIndex];
}

ListIterator::~ListIterator()
{
    delete[] this->elements;
}

ListIteratorException::ListIteratorException(const char* message)
{
    this->message = message;
}

const char* ListIteratorException::what() const throw()
{
    return this->message;
}
