#pragma once
#include "XLagCropDesc.generated.h"

USTRUCT(BlueprintType)
struct FXLagCropDesc
{
	GENERATED_BODY()

	// Название.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// Идентификатор.
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int ID;

	// Материал представления сельхозпродукта.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* CropPresentMaterial;
};