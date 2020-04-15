#pragma once
#include "HighQualificationService.h"
#include "LowQualificationService.h"
#include "VectorIterator.h"

class Tests
{
    void testVector();
    void VectorPush_ValidInput_PushedToVector();
    void VectorPop_NonEmptyVector_PoppedFromVector();
    void VectorAccess_ValidInput_ModifiedItem();
    void VectorInsert_ValidInput_InsertedToVector();
    void VectorRemove_ValidInput_RemovedFromVector();

    void testVectorIterator();
    void VectorIteratorCurrent_ValidIterator_ReturnCurrentElement();
    void VectorIteratorCurrent_InvalidIterator_RaiseException();
    void VectorIteratorNext_InvalidIterator_RaiseException();

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

    void testLowQualificationService();
    void LowQualificationServiceGetNextMaterial_NoArgument_ReturnNextMaterial();
    void LowQualificationServiceGetNextMaterial_SizeArgument_ReturnNextMaterial();
    void LowQualificationServiceSaveMaterial_NonEmptySavedList_SavedMaterial();
    void LowQualificationServiceGetMaterialsWithSizeAndMicrofragmentsQuantity_OneMaterialMatchesCondition_ReturnMatchingMaterial();
public:
    void RunAll();
};

