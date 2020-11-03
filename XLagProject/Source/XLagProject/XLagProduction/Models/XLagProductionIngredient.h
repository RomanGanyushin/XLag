#pragma once
#include "XLagProductionIngredient.generated.h"

USTRUCT(BlueprintType)
struct FXLagProductionIngredient
{
	GENERATED_BODY()

	// �������� ����������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	// ���� � ��������� � ��������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Share;
};