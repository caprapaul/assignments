#include "LowQualificationService.h"

#include "RepositoryCSV.h"
#include "RepositoryHTML.h"

using namespace std;

LowQualificationService::LowQualificationService(shared_ptr<Repository<Material>> repository, shared_ptr<Repository<Material>> saveRepository) :
    repository(repository),
    saveRepository(saveRepository)
{
}

LowQualificationService::~LowQualificationService()
{
}

Material LowQualificationService::GetNextMaterial()
{
    Material material = this->repository->GetNext([](Material material) { return true; });
    return material;
}

Material LowQualificationService::GetNextMaterial(string size)
{
    return this->repository->GetNext([size](Material material) { return material.Size() == size; });
}

void LowQualificationService::SaveMaterial(string id)
{
    Material material = this->repository->FindFirst([id](Material material) {return material.Id() == id; });
    this->saveRepository->Add(material);
}

vector<Material> LowQualificationService::GetSavedMaterials()
{
    return this->saveRepository->GetAll();
}

vector<Material> LowQualificationService::GetMaterialsWithSizeAndMicrofragmentsQuantity(string size, int microfragmentsQuantity)
{
    return this->repository->FindIf([size, microfragmentsQuantity](Material material) 
        {
            return material.Size() == size &&
                material.MicrofragmentsQuantity() >= microfragmentsQuantity;
        }
    );
}

string LowQualificationService::GetSaveFile()
{
    shared_ptr<RepositoryFile<Material>> fileRepository = dynamic_pointer_cast<RepositoryFile<Material>>(this->saveRepository);

    if (fileRepository)
    {
        return fileRepository->FilePath();
    }

    return string();
}

void LowQualificationService::SetSaveFile(string filePath)
{
    string extension = Utility::getFileExtension(filePath);

    if (extension == "csv" || extension == "txt")
    {
        this->saveRepository = make_shared<RepositoryCSV<Material>>();
    }
    else if (extension == "html")
    {
        this->saveRepository = make_shared<RepositoryHTML<Material>>
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
        throw LowQualificationServiceException("Invalid save file extension.");
    }

    shared_ptr<RepositoryFile<Material>> fileRepository = dynamic_pointer_cast<RepositoryFile<Material>>(this->saveRepository);

    if (fileRepository)
    {
        fileRepository->SetFilePath(filePath);
    }
}

void LowQualificationService::ClearSave()
{
    this->saveRepository->Clear();
}

void LowQualificationService::SetFile(std::string filePath)
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
        throw LowQualificationServiceException("Invalid file extension.");
    }

    shared_ptr<RepositoryFile<Material>> fileRepository = dynamic_pointer_cast<RepositoryFile<Material>>(this->repository);

    if (fileRepository)
    {
        fileRepository->SetFilePath(filePath);
    }
}

string LowQualificationService::GetFile()
{
    shared_ptr<RepositoryFile<Material>> fileRepository = dynamic_pointer_cast<RepositoryFile<Material>>(this->repository);

    if (fileRepository)
    {
        return fileRepository->FilePath();
    }

    return std::string();
}

LowQualificationServiceException::LowQualificationServiceException(string message)
{
    this->message = message;
}

const char* LowQualificationServiceException::what() const throw()
{
    return this->message.c_str();
}
