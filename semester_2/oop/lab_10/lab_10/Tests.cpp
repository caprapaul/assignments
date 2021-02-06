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

void Tests::testHighQualificationService()
{
    HighQualificationServiceAddMaterial_ValidInput_AddedMaterial();
    HighQualificationServiceAddMaterial_ExistingMaterial_ExceptionThrown();
    HighQualificationServiceRemoveMaterial_ExistingMaterial_RemovedMaterial();
    HighQualificationServiceUpdateMaterial_ExistingMaterial_UpdatedMaterial();
}

void Tests::HighQualificationServiceAddMaterial_ValidInput_AddedMaterial()
{
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.get()->Clear();

    service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    vector<Material> materials = service.GetMaterials();

    assert(materials.size() == 1);
}

void Tests::HighQualificationServiceAddMaterial_ExistingMaterial_ExceptionThrown()
{
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.get()->Clear();

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
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.get()->Clear();

    service.AddMaterial(string("test2"), "1X2X3", 1.0, 1, "test2.png");
    service.AddMaterial(string("test"), "1X2X3", 1.0, 1, "test.png");
    service.RemoveMaterial(string("test"));
    vector<Material> materials = service.GetMaterials();

    assert(materials.size() == 1);
}

void Tests::HighQualificationServiceUpdateMaterial_ExistingMaterial_UpdatedMaterial()
{
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService service(repository);

    service.SetFile("test.txt");
    repository.get()->Clear();

    service.AddMaterial("test2", "1X2X3", 1.0, 1, "test.png");
    service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    service.UpdateMaterial("test", "1X2X3", 1.0, 3, "test2.png");
    vector<Material> materials = service.GetMaterials();
    Material updated = materials[1];

    assert(updated.MicrofragmentsQuantity() == 3);
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
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.get()->Clear();

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
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.get()->Clear();

    highService.AddMaterial("test2", "2X2X2", 1.0, 1, "test.png");
    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");

    Material material = lowService.GetNextMaterial("1X2X3");
    assert(material.Id() == "test");
}

void Tests::LowQualificationServiceSaveMaterial_NonEmptySavedList_SavedMaterial()
{
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.get()->Clear();

    highService.AddMaterial("test2", "2X2X2", 1.0, 1, "test.png");
    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");

    lowService.SetSaveFile("test_save.html");
    lowService.ClearSave();
    lowService.SaveMaterial("test");
    lowService.SaveMaterial("test2");
    vector<Material> savedMaterials = lowService.GetSavedMaterials();

    assert(savedMaterials.size() == 2);
    assert(savedMaterials[0].Id() == "test");
}

void Tests::LowQualificationServiceGetMaterialsWithSizeAndMicrofragmentsQuantity_OneMaterialMatchesCondition_ReturnMatchingMaterial()
{
    shared_ptr<RepositoryText> repository = make_shared<RepositoryText>();
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.SetFile("test.txt");
    repository.get()->Clear();

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
    testHighQualificationService();
    testLowQualificationService();
}
