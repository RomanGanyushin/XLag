#pragma once
#include "XLagProductionIngredient.h"
#include "XLagProductionSchema.generated.h"

USTRUCT(BlueprintType)
struct FXLagProductionSchema
{
	GENERATED_BODY()

	// �������������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32  ID;
		
	// ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	FString Name;

	// ������������ ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Display;

	// ������������ �������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ProductPresentation;

	// ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FXLagProductionIngredient> Recipe;

	// ������������ ������������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductComplexity = 1.0f;

	// ��������� ������� ����������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TechnologyLevelRequired;

	// ���������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Density;
};
