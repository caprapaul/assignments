#include "LowQualificationService.h"

#include<memory>

using namespace std;

LowQualificationService::LowQualificationService(shared_ptr<RepositoryFile<Material>> repository) :
    repository(repository)
{
    this->savedMaterials = make_shared<RepositoryText>();
}


LowQualificationService::~LowQualificationService()
{
}

Material LowQualificationService::GetNextMaterial()
{
    Material material = this->repository.get()->GetNext([](Material material) { return true; });
    return material;
}

Material LowQualificationService::GetNextMaterial(string size)
{
    return this->repository.get()->GetNext([size](Material material) { return material.Size() == size; });
}

void LowQualificationService::SaveMaterial(string id)
{
    Material material = this->repository.get()->FindFirst([id](Material material) {return material.Id() == id; });
    this->savedMaterials.get()->Add(material);
}

vector<Material> LowQualificationService::GetSavedMaterials()
{
    return this->savedMaterials.get()->GetAll();
}

vector<Material> LowQualificationService::GetMaterialsWithSizeAndMicrofragmentsQuantity(string size, int microfragmentsQuantity)
{
    return this->repository.get()->FindIf([size, microfragmentsQuantity](Material material) 
        {
            return material.Size() == size &&
                material.MicrofragmentsQuantity() >= microfragmentsQuantity;
        }
    );
}

std::string LowQualificationService::GetSaveFilePath()
{
    return this->savedMaterials.get()->FilePath();
}

void LowQualificationService::SetSaveFile(string filePath)
{
    string extension = Utility::getFileExtension(filePath);

    if (extension == "csv")
    {
        this->savedMaterials = make_shared<RepositoryCSV>();
    }
    else if (extension == "html")
    {
        this->savedMaterials = make_shared<RepositoryHTML>();
    }
    else
    {
        throw LowQualificationServiceException("Invalid file extension.");
    }

    this->savedMaterials.get()->SetFilePath(filePath);
}

void LowQualificationService::ClearSave()
{
    this->savedMaterials.get()->Clear();
}

LowQualificationServiceException::LowQualificationServiceException(string message)
{
    this->message = message;
}

const char* LowQualificationServiceException::what() const throw()
{
    return this->message.c_str();
}
