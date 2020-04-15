#pragma once

#include "Material.h"
#include "Repository.h"

class LowQualificationService
{
    Repository<Material>& repository;
    Vector<Material> savedMaterials;

public:
    LowQualificationService(Repository<Material>& repository);
    LowQualificationService(LowQualificationService const& source);
    ~LowQualificationService();

    Material GetNextMaterial();
    Material GetNextMaterial(std::string size);
    void SaveMaterial(std::string id);
    Vector<Material> GetSavedMaterials();
    Vector<Material> GetMaterialsWithSizeAndMicrofragmentsQuantity(std::string size, int microfragmentsQuantity);
};

