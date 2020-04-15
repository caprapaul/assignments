#include "HighQualificationService.h"

using namespace std;

HighQualificationService::HighQualificationService(Repository<Material>& repository): 
    repository(repository)
{
}

HighQualificationService::HighQualificationService(HighQualificationService const& source): 
    repository(source.repository)
{
}

HighQualificationService::~HighQualificationService()
{
}

void HighQualificationService::AddMaterial(std::string id, std::string size, float infectionLevel, int microfragmentsQuantity, std::string photograph)
{
    Vector<Material> materialsWithId = repository.FindIf([&](Material material) { return material.Id() == id; });
    if (materialsWithId.Size() != 0)
    {
        throw HighQualificationServiceException("Id already exists.");
    }

    Material material(id, size, infectionLevel, microfragmentsQuantity, photograph);
    repository.Add(material);
}

void HighQualificationService::UpdateMaterial(std::string id, std::string newSize, float newInfectionLevel, int newMicrofragmentsQuantity, std::string newPhotograph)
{
    Vector<Material> materialsWithId = repository.FindIf([&](Material material) { return material.Id() == id; });
    if (materialsWithId.Size() == 0)
    {
        throw HighQualificationServiceException("Material with given id does not exist.");
    }

    Material newMaterial(id, newSize, newInfectionLevel, newMicrofragmentsQuantity, newPhotograph);
    this->repository.UpdateFirst([&](Material material) { return material.Id() == id; }, newMaterial);
}

void HighQualificationService::RemoveMaterial(std::string id)
{
    this->repository.RemoveFirst([id](Material material) { return material.Id() == id; });
}

Vector<Material> HighQualificationService::GetMaterials()
{
    return repository.GetAll();
}


HighQualificationServiceException::HighQualificationServiceException(string message)
{
    this->message = message;
}

const char* HighQualificationServiceException::what() const throw()
{
    return this->message.c_str();
}
