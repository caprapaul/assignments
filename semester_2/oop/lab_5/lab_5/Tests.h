#pragma once
#include "HighQualificationService.h"
#include "LowQualificationService.h"
#include "Repository.h"
#include "RepositoryText.h"
#include "RepositoryMemory.h"

class Tests
{
    void testMaterial();
    void Material_NoInput_MaterialCreated();

    void testRepository();
    void RepositoryAdd_ValidInput_AddedToRepository();
    void RepositoryRemoveIf_MultipleExistingElements_RemovedFromRepository();
    void RepositoryFindIf_ExistingElement_FoundInRepository();
    void RepositoryFindFirst_NonExistingElement_RaiseException();
    void RepositoryRemoveFirst_MultipleExistingElements_RemovedFirstFromRepository();
    void RepositoryUpdateFirst_MultipleExistingElements_UpdatedFirstFromRepository();
    void RepositoryGetNext_LoopElements_ReturnFirst();
    void RepositoryGetNext_NoElementFound_RaiseException();

    void testHighQualificationService();
    void HighQualificationServiceAddMaterial_ValidInput_AddedMaterial();
    void HighQualificationServiceAddMaterial_ExistingMaterial_ExceptionThrown();
    void HighQualificationServiceRemoveMaterial_ExistingMaterial_RemovedMaterial();
    void HighQualificationServiceUpdateMaterial_ExistingMaterial_UpdatedMaterial();
    void HighQualificationServiceUpdateMaterial_NonExistingMaterial_RaiseException();

    void testLowQualificationService();
    void LowQualificationServiceGetNextMaterial_NoArgument_ReturnNextMaterial();
    void LowQualificationServiceGetNextMaterial_SizeArgument_ReturnNextMaterial();
    void LowQualificationServiceSaveMaterial_NonEmptySavedList_SavedMaterial();
    void LowQualificationServiceGetMaterialsWithSizeAndMicrofragmentsQuantity_OneMaterialMatchesCondition_ReturnMatchingMaterial();
public:
    void RunAll();
};

