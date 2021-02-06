#include "MaterialValidator.h"

using namespace std;

ValidationException::ValidationException(std::string message)
{
    this->message = message;
}

const char* ValidationException::what() const throw()
{
    return this->message.c_str();
}

void MaterialValidator::validate(Material const& material)
{
    string errors;

    if (Utility::splitString(material.Size(), 'X').size() != 3)
    {
        errors += string("Invalid material size.\n");
    }

    if (errors.size() > 0)
    {
        throw ValidationException(errors);
    }
}
