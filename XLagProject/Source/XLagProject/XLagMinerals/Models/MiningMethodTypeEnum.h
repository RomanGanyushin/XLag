#pragma once
#include "MiningMethodTypeEnum.generated.h"

// Типы добычи.
UENUM(BlueprintType)
enum MiningMethodTypeEnum
{
	// Простой подбор.
	SimpleTake UMETA(DisplayName = "Simple Take"),

	// Открытый способ добычи.
	OpencastMining UMETA(DisplayName = "Opencast Mining"),

	// Шахтовы способ добычи.
	WellMining UMETA(DisplayName = "Classic Mining"),
};
