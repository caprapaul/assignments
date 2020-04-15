#include "VectorIterator.h"

VectorIteratorException::VectorIteratorException(char const* message)
{
    this->message = message;
}

char const* VectorIteratorException::what() const throw()
{
    return this->message;
}
