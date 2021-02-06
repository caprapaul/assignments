#pragma once

#include <memory>
#include <exception>

#include "RepositoryCSV.h"
#include "Domain.h"
#include "Astronomer.h"

class Service
{
private:
    std::shared_ptr<RepositoryFile<Domain>> repository;
    std::shared_ptr<RepositoryFile<Astronomer>> repositoryAstronomers;

public:
    Service(std::shared_ptr<RepositoryFile<Domain>> repository, std::shared_ptr<RepositoryFile<Astronomer>> repositoryAstronomers);
    ~Service();

    // Adds a star to the list.
    // Throws a ServiceException if name already exists, name is empty or diameter is not greater than 0.
    void AddStar(std::string name, std::string constellation, int ra, int dec, int diameter);
    void SaveSorted();
    std::vector<Domain> GetAllStars();
    std::vector<Astronomer> GetAllAstronomers();
    std::vector<Domain> GetFromConstellation(std::string constellation);
};

class ServiceException : public std::exception
{
private:
    const char* message;

public:
    ServiceException(const char* message);
    virtual const char* what() const throw();
};
