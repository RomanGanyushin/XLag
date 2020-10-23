#pragma once
#include "XLagCropStage.h"
#include "XLagCropDescription.generated.h"

USTRUCT(BlueprintType)
struct FXLagCropDescription
{
	GENERATED_BODY()

	// ��������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// �������������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int ID;

	// �������� ������������� ���������������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* CropPresentMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FXLagCropStage> CropStages;

	// ����� ����� ��������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TimeLife = 30;
};