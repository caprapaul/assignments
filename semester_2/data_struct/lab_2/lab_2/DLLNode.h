#pragma once

#include <tuple>

typedef int TElem;

class DLLNode
{
    friend class Matrix;

private:
    std::tuple<int, int, TElem> info;
    DLLNode* prev;
    DLLNode* next;

public:
    DLLNode(std::tuple<int, int, TElem> info, DLLNode* prev, DLLNode* next);
    ~DLLNode();
};

