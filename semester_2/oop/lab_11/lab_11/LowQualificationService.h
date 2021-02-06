#pragma once

#include "Material.h"
#include "Utility.h"
#include "Repository.h"

#include <memory>

class LowQualificationService
{
private:
    std::shared_ptr<Repository<Material>> repository;
    std::shared_ptr<Repository<Material>> saveRepository;

public:
    LowQualificationService(std::shared_ptr<Repository<Material>> repository, std::shared_ptr<Repository<Material>> saveRepository);
    ~LowQualificationService();

    Material GetNextMaterial();
    Material GetNextMaterial(std::string size);
    void SaveMaterial(std::string id);
    std::vector<Material> GetSavedMaterials();
    std::vector<Material> GetMaterialsWithSizeAndMicrofragmentsQuantity(std::string size, int microfragmentsQuantity);
    std::string GetSaveFile();
    void SetSaveFile(std::string filePath);
    void ClearSave();
    void SetFile(std::string filePath);
    std::string GetFile();
};

class LowQualificationServiceException : public std::exception
{
private:
    std::string message;

public:
    LowQualificationServiceException(std::string message);
    virtual const char* what() const throw();
};
