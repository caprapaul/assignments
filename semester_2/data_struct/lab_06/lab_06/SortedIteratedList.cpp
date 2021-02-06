#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

// Total complexity: Θ(n)
void SortedIteratedList::destroy(BSTNode** node)
{
    if ((*node) == nullptr)
    {
        return;
    }

    if ((*node)->left != nullptr)
    {
        destroy(&((*node)->left));
    }

    if ((*node)->right != nullptr)
    {
        destroy(&((*node)->right));
    }

    delete (*node);
}

SortedIteratedList::SortedIteratedList(Relation r)
{
    this->root = nullptr;
    this->_size = 0;
    this->compare = r;
}

// Total complexity: Θ(1)
int SortedIteratedList::size() const
{
    return this->_size;
}

// Total complexity: Θ(1)
bool SortedIteratedList::isEmpty() const 
{
    return this->_size == 0;
}

// Total complexity: Θ(n)
ListIterator SortedIteratedList::first() const
{
    ListIterator iterator(*this);
    iterator.first();

	return iterator;
}

// Total complexity: Θ(1)
TComp SortedIteratedList::getElement(ListIterator poz) const 
{
    return poz.getCurrent();
}

// Best case: Θ(1)  (remove root)
// Worst case: Θ(h) 
// Total complexity: O(h)
TComp SortedIteratedList::remove(ListIterator& poz) 
{
    int value = poz.getCurrent();
    BSTNode* currentNode = this->root;

    bool left = false;

    while (currentNode != nullptr && !currentNode->isRemoved && currentNode->info != value)
    {
        if (this->compare(value, currentNode->info))
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
    }

    if (currentNode != nullptr)
    {
        currentNode->isRemoved = true;
        this->_size--;

        return currentNode->info;
    }

    return NULL_TCOMP;
}

// Total complexity: Θ(n)
ListIterator SortedIteratedList::search(TComp e) const
{
    ListIterator iterator(*this);
    iterator.first();

    while (iterator.valid() && iterator.getCurrent() != e)
    {
        iterator.next();
    }

	return iterator;
}

// Total complexity: Θ(n)
void SortedIteratedList::add(TComp e) 
{
    BSTNode* newNode = new BSTNode(e);

    if (this->root == nullptr)
    {
        this->root = newNode;
        this->_size++;

        return;
    }

    BSTNode* currentNode = this->root;
    BSTNode* parentNode = currentNode;

    while (currentNode != nullptr)
    {
        parentNode = currentNode;

        if (this->compare(e, currentNode->info))
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
    }

    if (this->compare(e, parentNode->info))
    {
        parentNode->left = newNode;
    }
    else
    {
        parentNode->right = newNode;
    }

    this->_size++;
}

SortedIteratedList::~SortedIteratedList() 
{
    this->destroy(&(this->root));
}

BSTNode::BSTNode(TComp info, BSTNode* left, BSTNode* right)
{
    this->info = info;
    this->left = left;
    this->right = right;
}
