#include "Tests.h"
#include <cassert>
#include <string>

using namespace std;

void Tests::testMaterial()
{
    Material_NoInput_MaterialCreated();
}

void Tests::Material_NoInput_MaterialCreated()
{
    Material material;

    assert(material.Id() == "");
    assert(material.Size() == "0X0X0");
    assert(material.InfectionLevel() == 0.0);
    assert(material.MicrofragmentsQuantity() == 0);
    assert(material.Photograph() == "");
}

void Tests::testRepository()
{
    RepositoryAdd_ValidInput_AddedToRepository();
    RepositoryRemoveIf_MultipleExistingElements_RemovedFromRepository();
    RepositoryFindIf_ExistingElement_FoundInRepository();
    RepositoryRemoveFirst_MultipleExistingElements_RemovedFirstFromRepository();
    RepositoryUpdateFirst_MultipleExistingElements_UpdatedFirstFromRepository();
    RepositoryFindFirst_NonExistingElement_RaiseException();
    RepositoryGetNext_LoopElements_ReturnFirst();
    RepositoryGetNext_NoElementFound_RaiseException();
}

void Tests::RepositoryAdd_ValidInput_AddedToRepository()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(10);
    vector<int> elements = repository.GetAll();

    assert(elements.size() == 1);

    repository.Clear();
}

void Tests::RepositoryRemoveIf_MultipleExistingElements_RemovedFromRepository()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    repository.RemoveIf([&](int element) { return element == 10; });

    assert(repository.GetAll().size() == 1);
}

void Tests::RepositoryFindIf_ExistingElement_FoundInRepository()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    vector<int> found = repository.FindIf([&](int element) { return element == 10; });

    assert(found.size() == 2);
}

void Tests::RepositoryFindFirst_NonExistingElement_RaiseException()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(20);
    
    try
    {
        repository.FindFirst([&](int element) { return element == 10; });
        assert(false);
    }
    catch (exception& exception)
    {
        assert(true);
    }
}

void Tests::RepositoryRemoveFirst_MultipleExistingElements_RemovedFirstFromRepository()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    repository.RemoveFirst([&](int element) { return element == 10; });

    assert(repository.GetAll().size() == 2);
}

void Tests::RepositoryUpdateFirst_MultipleExistingElements_UpdatedFirstFromRepository()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    repository.UpdateFirst([&](int element) { return element == 10; }, 20);
    vector<int> found = repository.FindIf([&](int element) { return element == 10; });

    assert(found.size() == 1);
}

void Tests::RepositoryGetNext_LoopElements_ReturnFirst()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(10);
    repository.GetNext([](int element) { return true; });

    int next = repository.GetNext([](int element) { return true; });
    assert(next == 10);
}

void Tests::RepositoryGetNext_NoElementFound_RaiseException()
{
    RepositoryText<int> repository;

    repository.SetFile("test.txt");
    repository.Clear();

    repository.Add(10);

    try
    {
        repository.GetNext([](int element) { return false; });
        assert(false);
    }
    catch (exception& exception)
    {
        exception.what();
        assert(true);
    }
}

void Tests::testHighQualificationService()
{
    HighQualificationServiceAddMaterial_ValidInput_AddedMaterial();
    HighQualificationServiceAddMaterial_ExistingMaterial_ExceptionThrown();
    HighQualificationServiceRemoveMaterial_ExistingMaterial_RemovedMaterial();
    HighQualificationServiceUpdateMaterial_ExistingMaterial_UpdatedMaterial();
    HighQualificationServiceUpdateMaterial_NonExistingMaterial_RaiseException();
}

void Tests::HighQualificationServiceAddMaterial_ValidInput_AddedMaterial()
{
    RepositoryText<Material> repository;
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.Clear();

    service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    vector<Material> materials = service.GetMaterials();

    assert(materials.size() == 1);
}

void Tests::HighQualificationServiceAddMaterial_ExistingMaterial_ExceptionThrown()
{
    RepositoryText<Material> repository;
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.Clear();

    service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    try
    {
        service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
        assert(false);
    }
    catch (exception& exception)
    {
        exception.what();
        assert(true);
    }
    vector<Material> materials = service.GetMaterials();

    assert(materials.size() == 1);
}

void Tests::HighQualificationServiceRemoveMaterial_ExistingMaterial_RemovedMaterial()
{
    RepositoryText<Material> repository;
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.Clear();

    service.AddMaterial(string("test2"), "1X2X3", 1.0, 1, "test2.png");
    service.AddMaterial(string("test"), "1X2X3", 1.0, 1, "test.png");
    service.RemoveMaterial(string("test"));
    vector<Material> materials = service.GetMaterials();

    assert(materials.size() == 1);
}

void Tests::HighQualificationServiceUpdateMaterial_ExistingMaterial_UpdatedMaterial()
{
    RepositoryText<Material> repository;
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.Clear();

    service.AddMaterial("test2", "1X2X3", 1.0, 1, "test.png");
    service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    service.UpdateMaterial("test", "1X2X3", 1.0, 3, "test2.png");
    vector<Material> materials = service.GetMaterials();
    Material updated = materials[1];

    assert(updated.MicrofragmentsQuantity() == 3);
}

void Tests::HighQualificationServiceUpdateMaterial_NonExistingMaterial_RaiseException()
{
    RepositoryText<Material> repository;
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.Clear();

    service.AddMaterial("test2", "1X2X3", 1.0, 1, "test.png");

    try 
    {
        service.UpdateMaterial("test", "1X2X3", 1.0, 3, "test2.png");
        assert(false);
    }
    catch (exception& exception)
    {
        exception.what();
        assert(true);
    }
}

void Tests::testLowQualificationService()
{
    LowQualificationServiceGetNextMaterial_NoArgument_ReturnNextMaterial();
    LowQualificationServiceGetNextMaterial_SizeArgument_ReturnNextMaterial();
    LowQualificationServiceSaveMaterial_NonEmptySavedList_SavedMaterial();
    LowQualificationServiceGetMaterialsWithSizeAndMicrofragmentsQuantity_OneMaterialMatchesCondition_ReturnMatchingMaterial();
}

void Tests::LowQualificationServiceGetNextMaterial_NoArgument_ReturnNextMaterial()
{
    RepositoryText<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.Clear();

    highService.AddMaterial("test2", "1X2X3", 1.0, 1, "test.png");
    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");

    Material material = lowService.GetNextMaterial();
    assert(material.Id() == "test2");
    assert(material.Size() == "1X2X3");
    assert(material.InfectionLevel() == 1.0);
    assert(material.MicrofragmentsQuantity() == 1);
    assert(material.Photograph() == "test.png");

    material = lowService.GetNextMaterial();
    assert(material.Id() == "test");
}

void Tests::LowQualificationServiceGetNextMaterial_SizeArgument_ReturnNextMaterial()
{
    RepositoryText<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.Clear();

    highService.AddMaterial("test2", "2X2X2", 1.0, 1, "test.png");
    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");

    Material material = lowService.GetNextMaterial("1X2X3");
    assert(material.Id() == "test");
}

void Tests::LowQualificationServiceSaveMaterial_NonEmptySavedList_SavedMaterial()
{
    RepositoryText<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.Clear();

    highService.AddMaterial("test2", "2X2X2", 1.0, 1, "test.png");
    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");

    lowService.SaveMaterial("test");
    vector<Material> savedMaterials = lowService.GetSavedMaterials();

    assert(savedMaterials.size() == 1);
    assert(savedMaterials[0].Id() == "test");
}

void Tests::LowQualificationServiceGetMaterialsWithSizeAndMicrofragmentsQuantity_OneMaterialMatchesCondition_ReturnMatchingMaterial()
{
    RepositoryText<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.Clear();

    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    highService.AddMaterial("test2", "2X2X2", 1.0, 15, "test.png");
    highService.AddMaterial("test3", "2X2X2", 1.0, 5, "test.png");
    highService.AddMaterial("test4", "1X2X3", 1.0, 11, "test.png");

    vector<Material> foundMaterials = lowService.GetMaterialsWithSizeAndMicrofragmentsQuantity("2X2X2", 10);

    assert(foundMaterials.size() == 1);
    assert(foundMaterials[0].Id() == "test2");
}

void Tests::RunAll()
{
    testMaterial();
    testRepository();
    testHighQualificationService();
    testLowQualificationService();
}
