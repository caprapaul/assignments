#include "Repository.h"

RepositoryException::RepositoryException(char const* message)
{
    this->message = message;
}

char const* RepositoryException::what() const throw()
{
    return this->message;
}
