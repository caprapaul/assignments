#include "DLLNode.h"

using namespace std;

DLLNode::DLLNode(tuple<int, int, TElem> info, DLLNode * prev, DLLNode * next)
{
    this->info = info;
    this->prev = prev;
    this->next = next;
}

DLLNode::~DLLNode()
{
}
