#pragma once

#include "Material.h"
#include "RepositoryText.h"

class LowQualificationService
{
    RepositoryText<Material>& repository;
    std::vector<Material> savedMaterials;

public:
    LowQualificationService(RepositoryText<Material>& repository);
    ~LowQualificationService();

    Material GetNextMaterial();
    Material GetNextMaterial(std::string size);
    void SaveMaterial(std::string id);
    std::vector<Material> GetSavedMaterials();
    std::vector<Material> GetMaterialsWithSizeAndMicrofragmentsQuantity(std::string size, int microfragmentsQuantity);
};

