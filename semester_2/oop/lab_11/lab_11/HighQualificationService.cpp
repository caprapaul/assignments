#include "HighQualificationService.h"

#include "RepositoryFile.h"
#include "RepositoryCSV.h"
#include "RepositoryHTML.h"

using namespace std;

HighQualificationService::HighQualificationService(shared_ptr<Repository<Material>> repository):
    repository(repository)
{
}


HighQualificationService::~HighQualificationService()
{
}

void HighQualificationService::AddMaterial(string id, string size, float infectionLevel, int microfragmentsQuantity, string photograph)
{
    vector<Material> materialsWithId = this->repository->FindIf([&](Material material) { return material.Id() == id; });
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

    this->repository->Add(material);
}

void HighQualificationService::UpdateMaterial(string id, string newSize, float newInfectionLevel, int newMicrofragmentsQuantity, string newPhotograph)
{
    vector<Material> materialsWithId = this->repository->FindIf([&](Material material) { return material.Id() == id; });
    if (materialsWithId.size() == 0)
    {
        throw HighQualificationServiceException("Material with given id does not exist.");
    }

    Material newMaterial(id, newSize, newInfectionLevel, newMicrofragmentsQuantity, newPhotograph);
    this->repository->UpdateFirst([&](Material material) { return material.Id() == id; }, newMaterial);
}

void HighQualificationService::RemoveMaterial(string id)
{
    this->repository->RemoveFirst([id](Material material) { return material.Id() == id; });
}

vector<Material> HighQualificationService::GetMaterials()
{
    return this->repository->GetAll();
}

void HighQualificationService::SetFile(std::string filePath)
{
    string extension = Utility::getFileExtension(filePath);

    if (extension == "csv" || extension == "txt")
    {
        this->repository = make_shared<RepositoryCSV<Material>>();
    }
    else if (extension == "html")
    {
        this->repository = make_shared<RepositoryHTML<Material>>
        (
            "Saved Materials",
            vector<string>
            {
                "Id",
                "Size",
                "Infection Level",
                "Microfragments Quantity",
                "Photograph"
            }
        );
    }
    else
    {
        throw HighQualificationServiceException("Invalid file extension.");
    }

    shared_ptr<RepositoryFile<Material>> fileRepository = dynamic_pointer_cast<RepositoryFile<Material>>(this->repository);

    if (fileRepository)
    {
        fileRepository->SetFilePath(filePath);
    }
}

string HighQualificationService::GetFile()
{
    shared_ptr<RepositoryFile<Material>> fileRepository = dynamic_pointer_cast<RepositoryFile<Material>>(this->repository);

    if (fileRepository)
    {
        return fileRepository->FilePath();
    }   

    return std::string();
}


HighQualificationServiceException::HighQualificationServiceException(string message)
{
    this->message = message;
}

const char* HighQualificationServiceException::what() const throw()
{
    return this->message.c_str();
}
