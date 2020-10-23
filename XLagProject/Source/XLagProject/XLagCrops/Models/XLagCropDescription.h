#pragma once
#include "XLagCropStage.h"
#include "XLagCropDescription.generated.h"

USTRUCT(BlueprintType)
struct FXLagCropDescription
{
	GENERATED_BODY()

	// Название.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// Идентификатор.
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int ID;

	// Материал представления сельхозпродукта.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* CropPresentMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FXLagCropStage> CropStages;

	// Время роста растения.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TimeLife = 30;
};