#pragma once

#include "Material.h"
#include "Utility.h"
#include "RepositoryFile.h"
#include "RepositoryText.h"
#include "RepositoryCSV.h"
#include "RepositoryHTML.h"

class LowQualificationService
{
private:
    std::shared_ptr<RepositoryFile<Material>> repository;
    std::shared_ptr<RepositoryFile<Material>> savedMaterials;

public:
    LowQualificationService(std::shared_ptr<RepositoryFile<Material>> repository);
    ~LowQualificationService();

    Material GetNextMaterial();
    Material GetNextMaterial(std::string size);
    void SaveMaterial(std::string id);
    std::vector<Material> GetSavedMaterials();
    std::vector<Material> GetMaterialsWithSizeAndMicrofragmentsQuantity(std::string size, int microfragmentsQuantity);
    std::string GetSaveFilePath();
    void SetSaveFile(std::string filePath);
    void ClearSave();
};

class LowQualificationServiceException : public std::exception
{
private:
    std::string message;

public:
    LowQualificationServiceException(std::string message);
    virtual const char* what() const throw();
};
