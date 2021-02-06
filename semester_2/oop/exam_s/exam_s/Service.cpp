#include "Service.h"

#include <string>
#include <assert.h>

using namespace std;

Service::Service(std::shared_ptr<RepositoryFile<Domain>> repository, std::shared_ptr<RepositoryFile<Astronomer>> repositoryAstronomers)
{
    this->repository = repository;
    this->repositoryAstronomers = repositoryAstronomers;
}

Service::~Service()
{
}

void Service::AddStar(std::string name, std::string constellation, int ra, int dec, int diameter)
{
    if (name.empty())
    {
        throw ServiceException("Name cannot be empty.");
    }

    if (diameter <= 0)
    {
        throw ServiceException("Diameter must be greater than 0.");
    }

    vector<Domain> elements = this->repository->FindIf
    (
        [&](Domain element)
        {
            return element.Name() == name;
        }
    );

    if (elements.size() > 0)
    {
        throw ServiceException("There already exists a star with the given name.");
    }

    Domain element(name, constellation, ra, dec, diameter);

    this->repository->Add(element);
}

void Service::SaveSorted()
{
    vector<Domain> elements = this->repository->GetAll();

    this->repository->Clear();

    std::sort(elements.begin() + 4, elements.end(), 
        [&](Domain d1, Domain d2) 
        {
            return d1.Constellation() < d2.Constellation();
        }
    );

    for (Domain element : elements)
    {
        this->repository->Add(element);
    }
}

vector<Domain> Service::GetAllStars()
{
    vector<Domain> elements = this->repository->GetAll();

    return elements;
}

std::vector<Astronomer> Service::GetAllAstronomers()
{
    vector<Astronomer> elements = this->repositoryAstronomers->GetAll();

    return elements;
}

vector<Domain> Service::GetFromConstellation(std::string constellation)
{
    vector<Domain> elements = this->repository->FindIf
    (
        [&](Domain element)
        {
            return element.Constellation() == constellation;
        }
    );

    return elements;
}

ServiceException::ServiceException(const char * message)
{
    this->message = message;
}

const char * ServiceException::what() const throw()
{
    return this->message;
}
