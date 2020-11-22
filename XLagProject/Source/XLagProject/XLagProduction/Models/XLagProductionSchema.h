#pragma once
#include "XLagProductionIngredient.h"
#include "XLagProductionSchema.generated.h"

USTRUCT(BlueprintType)
struct FXLagProductionSchema
{
	GENERATED_BODY()

	// Идентификатор
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32  ID;
		
	// Название
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	FString Name;

	// Отображаемое название
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Display;

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
