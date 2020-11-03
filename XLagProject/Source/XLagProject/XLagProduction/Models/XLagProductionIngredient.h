#pragma once
#include "XLagProductionIngredient.generated.h"

USTRUCT(BlueprintType)
struct FXLagProductionIngredient
{
	GENERATED_BODY()

	// Название компонента.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	// Доля в процентах в продукте.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Share;
};