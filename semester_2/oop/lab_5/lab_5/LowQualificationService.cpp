#include "LowQualificationService.h"

LowQualificationService::LowQualificationService(Repository<Material>& repository) :
    repository(repository)
{
}

LowQualificationService::LowQualificationService(LowQualificationService const& source) :
    repository(source.repository)
{
}

LowQualificationService::~LowQualificationService()
{
}

Material LowQualificationService::GetNextMaterial()
{
    Material material = this->repository.GetNext([](Material material) { return true; });
    return material;
}

Material LowQualificationService::GetNextMaterial(std::string size)
{
    return this->repository.GetNext([size](Material material) { return material.Size() == size; });
}

void LowQualificationService::SaveMaterial(std::string id)
{
    Material material = this->repository.FindFirst([id](Material material) {return material.Id() == id; });
    this->savedMaterials.Push(material);
}

Vector<Material> LowQualificationService::GetSavedMaterials()
{
    return this->savedMaterials;
}

Vector<Material> LowQualificationService::GetMaterialsWithSizeAndMicrofragmentsQuantity(std::string size, int microfragmentsQuantity)
{
    return this->repository.FindIf([size, microfragmentsQuantity](Material material) 
        {
            return material.Size() == size &&
                material.MicrofragmentsQuantity() >= microfragmentsQuantity;
        }
    );
}
