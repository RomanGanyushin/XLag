#pragma once
#include "CellOperationEnum.generated.h"

UENUM(BlueprintType)
enum CellOperationEnum
{
	Sow,
	Grow,
	// Показывет процент выполнения операции.
	Evolution,
	// Показвает время необъодимое для выполнение операции.
	EvolutionTime,
	CropQuantity,

	// Показывает статус поиск минерала
	SearchMineral,
};