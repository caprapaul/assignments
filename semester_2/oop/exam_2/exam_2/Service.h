#pragma once

#include <memory>

#include "RepositoryCSV.h"
#include "Domain.h"

class Service
{
private:
    std::shared_ptr<RepositoryFile<Domain>> repository;

public:
    Service(std::shared_ptr<RepositoryFile<Domain>> repository);
    ~Service();

    std::vector<Domain> GetAll();

    // Returns the number of cars with a given manufacturer. (case sensitive)
    // In: manufacturer(string) - the manufacturer
    // Out: the number of cars with the given manufacturer
    int GetNumberOfCarsForManufacturer(std::string manufacturer);

    void TestGetNumberOfCarsForManufacturer();
};

