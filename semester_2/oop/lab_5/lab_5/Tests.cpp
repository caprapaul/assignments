#include "Tests.h"
#include <cassert>
#include <string>

using namespace std;

void Tests::testVector()
{
    VectorPush_ValidInput_PushedToVector();
    VectorPop_NonEmptyVector_PoppedFromVector();
    VectorAccess_ValidInput_ModifiedItem();
    VectorInsert_ValidInput_InsertedToVector();
    VectorRemove_ValidInput_RemovedFromVector();
}

void Tests::VectorPush_ValidInput_PushedToVector()
{
    Vector<int> vector;

    vector.Push(10);

    assert(vector.Size() == 1);
}

void Tests::VectorPop_NonEmptyVector_PoppedFromVector()
{
    Vector<int> vector;

    vector.Push(10);
    int popped = vector.Pop();

    assert(vector.Size() == 0);
    assert(popped = 10);
}

void Tests::VectorAccess_ValidInput_ModifiedItem()
{
    Vector<int> vector;

    vector.Push(10);
    vector.Push(20);
    int first = vector[0];

    assert(first == 10);
}

void Tests::VectorInsert_ValidInput_InsertedToVector()
{
    Vector<int> vector;

    vector.Push(20);
    vector.Insert(0, 10);
    int first = vector[0];

    assert(vector.Size() == 2);
    assert(first == 10);
}

void Tests::VectorRemove_ValidInput_RemovedFromVector()
{
    Vector<int> vector;

    vector.Push(20);
    vector.Push(10);
    vector.Remove(0);
    int first = vector[0];

    assert(vector.Size() == 1);
    assert(first == 10);
}

void Tests::testVectorIterator()
{
    VectorIteratorCurrent_ValidIterator_ReturnCurrentElement();
    VectorIteratorNext_InvalidIterator_RaiseException();
    VectorIteratorCurrent_InvalidIterator_RaiseException();
}

void Tests::VectorIteratorCurrent_ValidIterator_ReturnCurrentElement()
{
    Vector<int> vector;
    VectorIterator<int> iterator = vector.Iterator();
    vector.Push(10);
    iterator.First();

    assert(iterator.Current() == 10);
}

void Tests::VectorIteratorCurrent_InvalidIterator_RaiseException()
{
    Vector<int> vector;
    VectorIterator<int> iterator = vector.Iterator();

    try
    {
        iterator.Current();
        assert(false);
    }
    catch (exception& exception)
    {
        exception.what();
        assert(true);
    }

}

void Tests::VectorIteratorNext_InvalidIterator_RaiseException()
{
    Vector<int> vector;
    VectorIterator<int> iterator = vector.Iterator();

    try
    {
        iterator.Next();
        assert(false);
    }
    catch (exception& exception)
    {
        exception.what();
        assert(true);
    }
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
    Repository<int> repository;

    repository.Add(10);
    Vector<int> elements = repository.GetAll();

    assert(elements.Size() == 1);
}

void Tests::RepositoryRemoveIf_MultipleExistingElements_RemovedFromRepository()
{
    Repository<int> repository;

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    repository.RemoveIf([&](int element) { return element == 10; });

    assert(repository.GetAll().Size() == 1);
}

void Tests::RepositoryFindIf_ExistingElement_FoundInRepository()
{
    Repository<int> repository;

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    Vector<int> found = repository.FindIf([&](int element) { return element == 10; });

    assert(found.Size() == 2);
}

void Tests::RepositoryFindFirst_NonExistingElement_RaiseException()
{
    Repository<int> repository;

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
    Repository<int> repository;

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    repository.RemoveFirst([&](int element) { return element == 10; });

    assert(repository.GetAll().Size() == 2);
}

void Tests::RepositoryUpdateFirst_MultipleExistingElements_UpdatedFirstFromRepository()
{
    Repository<int> repository;

    repository.Add(10);
    repository.Add(20);
    repository.Add(10);
    repository.UpdateFirst([&](int element) { return element == 10; }, 20);
    Vector<int> found = repository.FindIf([&](int element) { return element == 10; });

    assert(found.Size() == 1);
}

void Tests::RepositoryGetNext_LoopElements_ReturnFirst()
{
    Repository<int> repository;

    repository.Add(10);
    repository.GetNext([](int element) { return true; });

    int next = repository.GetNext([](int element) { return true; });
    assert(next == 10);
}

void Tests::RepositoryGetNext_NoElementFound_RaiseException()
{
    Repository<int> repository;

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
}

void Tests::HighQualificationServiceAddMaterial_ValidInput_AddedMaterial()
{
    Repository<Material> repository;
    HighQualificationService service(repository);

    service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    Vector<Material> materials = service.GetMaterials();

    assert(materials.Size() == 1);
}

void Tests::HighQualificationServiceAddMaterial_ExistingMaterial_ExceptionThrown()
{
    Repository<Material> repository;
    HighQualificationService service(repository);

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
    Vector<Material> materials = service.GetMaterials();

    assert(materials.Size() == 1);
}

void Tests::HighQualificationServiceRemoveMaterial_ExistingMaterial_RemovedMaterial()
{
    Repository<Material> repository;
    HighQualificationService service(repository);

    service.AddMaterial(string("test2"), "1X2X3", 1.0, 1, "test2.png");
    service.AddMaterial(string("test"), "1X2X3", 1.0, 1, "test.png");
    service.RemoveMaterial(string("test"));
    Vector<Material> materials = service.GetMaterials();

    assert(materials.Size() == 1);
}

void Tests::HighQualificationServiceUpdateMaterial_ExistingMaterial_UpdatedMaterial()
{
    Repository<Material> repository;
    HighQualificationService service(repository);

    service.AddMaterial("test2", "1X2X3", 1.0, 1, "test.png");
    service.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    service.UpdateMaterial("test", "1X2X3", 1.0, 3, "test2.png");
    Vector<Material> materials = service.GetMaterials();
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
    Repository<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

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
    Repository<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.AddMaterial("test2", "2X2X2", 1.0, 1, "test.png");
    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");

    Material material = lowService.GetNextMaterial("1X2X3");
    assert(material.Id() == "test");
}

void Tests::LowQualificationServiceSaveMaterial_NonEmptySavedList_SavedMaterial()
{
    Repository<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.AddMaterial("test2", "2X2X2", 1.0, 1, "test.png");
    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");

    lowService.SaveMaterial("test");
    Vector<Material> savedMaterials = lowService.GetSavedMaterials();

    assert(savedMaterials.Size() == 1);
    assert(savedMaterials[0].Id() == "test");
}

void Tests::LowQualificationServiceGetMaterialsWithSizeAndMicrofragmentsQuantity_OneMaterialMatchesCondition_ReturnMatchingMaterial()
{
    Repository<Material> repository;
    HighQualificationService highService(repository);
    LowQualificationService lowService(repository);

    highService.AddMaterial("test", "1X2X3", 1.0, 1, "test.png");
    highService.AddMaterial("test2", "2X2X2", 1.0, 15, "test.png");
    highService.AddMaterial("test3", "2X2X2", 1.0, 5, "test.png");
    highService.AddMaterial("test4", "1X2X3", 1.0, 11, "test.png");

    Vector<Material> foundMaterials = lowService.GetMaterialsWithSizeAndMicrofragmentsQuantity("2X2X2", 10);

    assert(foundMaterials.Size() == 1);
    assert(foundMaterials[0].Id() == "test2");
}

void Tests::RunAll()
{
    testVector();
    testVectorIterator();
    testRepository();
    testHighQualificationService();
    testLowQualificationService();
}
