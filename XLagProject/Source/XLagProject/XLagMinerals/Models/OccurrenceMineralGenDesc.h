#pragma once

#include "..\..\Common\TerrainElementEnum.h"
#include "OccurrenceMineralGenDesc.generated.h"

USTRUCT(BlueprintType)
struct FOccurrenceMineralGenDesc
{
	GENERATED_BODY()

	// Концентрация 0-1. 
	// 1 - Распределение будет концентрироваться в одном месте.
	// 2 - Распределение будет равномерно распределно по карте.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Density;

	// Среднее количество вещества на 1 кв.м.
	// Общее количество ресурса = площадь игрового мира x AverageQuantity.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AverageQuantity;

	// Полупериод востановления ресурсов (в днях).
	// 0 - мгновенное востановение.
	// -1 - не востанавливаетя.
	// n - за это количество дней, востановится половина выбранного ресурс. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int RecoveryHalfTime;

	// Элеменет ланшафта, под котором залегает ресурс.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<TerrainElementEnum> UnderTerrainElement;
};