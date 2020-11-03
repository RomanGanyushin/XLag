#pragma once
#include "XLagProductionIngredient.h"
#include "XLagProductionSchema.generated.h"

USTRUCT(BlueprintType)
struct FXLagProductionSchema
{
	GENERATED_BODY()

	// Название
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	FString Name;

	// Предсавление изделия.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ProductPresentation;

	// Рецепт.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FXLagProductionIngredient> Recipe;

	// Трудоемкость производства.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductComplexity = 1.0f;

	// Требуемый уровень технологии.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TechnologyLevelRequired;

	// Плотность.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Density;
};
