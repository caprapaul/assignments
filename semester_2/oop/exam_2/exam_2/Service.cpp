#include "Service.h"

#include <string>
#include <assert.h>

using namespace std;

Service::Service(std::shared_ptr<RepositoryFile<Domain>> repository)
{
    this->repository = repository;
}

Service::~Service()
{
}

vector<Domain> Service::GetAll()
{
    vector<Domain> elements = this->repository->GetAll();
    sort
    (
        elements.begin(), 
        elements.end(), 
        [&](Domain element1, Domain element2) 
        {
            return element1.Manufacturer() < element2.Manufacturer();
        }
    );

    return elements;
}

int Service::GetNumberOfCarsForManufacturer(std::string manufacturer)
{
    vector<Domain> elements = this->repository->FindIf
    (
        [&](Domain element)
        {
            return element.Manufacturer() == manufacturer;
        }
    );

    return elements.size();
}

void Service::TestGetNumberOfCarsForManufacturer()
{
    assert(this->GetNumberOfCarsForManufacturer("Toyota") == 2);
    assert(this->GetNumberOfCarsForManufacturer("a") == 0);
    assert(this->GetNumberOfCarsForManufacturer("toyota") == 0);
}
