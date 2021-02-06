#pragma once

#include <exception>
#include <string>
#include <memory>

#include "Repository.h"
#include "Material.h"
#include "MaterialValidator.h"

class HighQualificationService
{
private:
    std::shared_ptr<Repository<Material>> repository;

public:
    HighQualificationService(std::shared_ptr<Repository<Material>> repository);
    ~HighQualificationService();

    void AddMaterial(std::string id, std::string size, float infectionLevel, int microfragmentsQuantity, std::string photograph);
    void UpdateMaterial(std::string id, std::string newSize, float newInfectionLevel, int newMicrofragmentsQuantity, std::string newPhotograph);
    void RemoveMaterial(std::string id);
    std::vector<Material> GetMaterials();
    void SetFile(std::string filePath);
    std::string GetFile();
};

class HighQualificationServiceException : public std::exception
{
private:
    std::string message;

public:
    HighQualificationServiceException(std::string message);
    virtual const char* what() const throw();
};
