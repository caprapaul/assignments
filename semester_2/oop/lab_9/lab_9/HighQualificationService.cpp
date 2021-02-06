#include "HighQualificationService.h"

using namespace std;

HighQualificationService::HighQualificationService(shared_ptr<RepositoryFile<Material>> repository):
    repository(repository)
{
}


HighQualificationService::~HighQualificationService()
{
}

void HighQualificationService::AddMaterial(string id, string size, float infectionLevel, int microfragmentsQuantity, string photograph)
{
    vector<Material> materialsWithId = this->repository.get()->FindIf([&](Material material) { return material.Id() == id; });
    if (materialsWithId.size() != 0)
    {
        throw HighQualificationServiceException("Id already exists.");
    }

    Material material(id, size, infectionLevel, microfragmentsQuantity, photograph);
    try 
    {
        MaterialValidator::validate(material);
    }
    catch (exception& exception)
    {
        throw HighQualificationServiceException(exception.what());
    }

    this->repository.get()->Add(material);
}

void HighQualificationService::UpdateMaterial(string id, string newSize, float newInfectionLevel, int newMicrofragmentsQuantity, string newPhotograph)
{
    vector<Material> materialsWithId = this->repository.get()->FindIf([&](Material material) { return material.Id() == id; });
    if (materialsWithId.size() == 0)
    {
        throw HighQualificationServiceException("Material with given id does not exist.");
    }

    Material newMaterial(id, newSize, newInfectionLevel, newMicrofragmentsQuantity, newPhotograph);
    this->repository.get()->UpdateFirst([&](Material material) { return material.Id() == id; }, newMaterial);
}

void HighQualificationService::RemoveMaterial(string id)
{
    this->repository.get()->RemoveFirst([id](Material material) { return material.Id() == id; });
}

vector<Material> HighQualificationService::GetMaterials()
{
    return this->repository.get()->GetAll();
}

void HighQualificationService::SetFile(std::string filePath)
{
    this->repository.get()->SetFilePath(filePath);
}


HighQualificationServiceException::HighQualificationServiceException(string message)
{
    this->message = message;
}

const char* HighQualificationServiceException::what() const throw()
{
    return this->message.c_str();
}
