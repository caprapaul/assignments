#pragma once

#include <exception>
#include <string>

#include "Repository.h"
#include "Material.h"

class HighQualificationService
{
private:
    Repository<Material>& repository;

public:
    HighQualificationService(Repository<Material>& repository);
    HighQualificationService(HighQualificationService const& source);
    ~HighQualificationService();

    void AddMaterial(std::string id, std::string size, float infectionLevel, int microfragmentsQuantity, std::string photograph);
    void UpdateMaterial(std::string id, std::string newSize, float newInfectionLevel, int newMicrofragmentsQuantity, std::string newPhotograph);
    void RemoveMaterial(std::string id);
    Vector<Material> GetMaterials();
};

class HighQualificationServiceException : public std::exception
{
private:
    std::string message;

public:
    HighQualificationServiceException(std::string message);
    virtual const char* what() const throw();
};
