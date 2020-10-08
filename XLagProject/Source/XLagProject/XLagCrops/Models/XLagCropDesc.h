#pragma once
#include "XLagCropDesc.generated.h"

USTRUCT(BlueprintType)
struct FXLagCropDesc
{
	GENERATED_BODY()

	// ��������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// �������������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int ID;

	// �������� ������������� ���������������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* CropPresentMaterial;
};