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

