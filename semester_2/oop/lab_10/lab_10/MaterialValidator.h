#pragma once

#include "Material.h"
#include "Utility.h"
#include <string>
#include <exception>

class MaterialValidator
{
public:
    static void validate(Material const& material);
};

class ValidationException : public std::exception
{
private:
    std::string message;

public:
    ValidationException(std::string message);
    virtual const char* what() const throw();
};
