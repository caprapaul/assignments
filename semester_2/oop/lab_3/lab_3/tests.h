#pragma once

#include "vector.h"
#include "barricade.h"
#include "repository.h"
#include "service.h"

void VectorCreate_ValidInput_Success();
void VectorDestroy_ValidInput_Success();
void VectorGet_IndexOutOfRange_Error();
void VectorPush_ValidInput_PushedToVector();
void VectorPop_NonEmptyVector_PoppedFromVector();
void VectorPop_EmptyVector_Error();
void VectorInsert_ValidInput_InsertedToVector();
void VectorInsert_IndexOutOfRange_Error();
void VectorRemove_ValidInput_RemovedFromVector();
void VectorRemove_IndexOutOfRange_Error();
void VectorSet_ValidInput_ModifiedItem();
void VectorSet_IndexOutOfRange_Error();

void TestVector();

void BarricadeCreate_ValidInput_Success();
void BarricadeDestroy_ValidInput_Success();
void BarricadeEqual_SameLocationCode_ReturnsOne();
void BarricadeEqual_DifferentLocationCode_ReturnsZero();
void BarricadeCopy_ValidInput_CopiedBarricade();
void BarricadeCompareType_SameType_ReturnsOne();
void BarricadeCompareType_DifferentType_ReturnsZero();

void TestBarricade();

void RepositoryCreate_ValidInput_Success();
void RepositoryDestroy_ValidInput_Success();
void RepositoryAdd_ValidInput_AddedElement();
void RepositoryAdd_DuplicateElement_Error();
void RepositoryRemove_ValidInput_RemovedElement();
void RepositoryUpdate_ValidInput_UpdatedElement();
void RepositorySearch_ValidInput_FoundElement();

void TestRepository();

void ServiceCreate_ValidInput_Success();
void ServiceDestroy_ValidInput_Success();
void ServiceAdd_ValidInput_AddedToRepository();
void ServiceRemove_ValidInput_RemovedFromRepository();
void ServiceSearchBarricadeType_ValidInput_FoundBarricade();
void ServiceUndo_ExistingOperation_UndidOperation();
void ServiceRedo_ExistingOperation_RedidOperation();

void TestService();
