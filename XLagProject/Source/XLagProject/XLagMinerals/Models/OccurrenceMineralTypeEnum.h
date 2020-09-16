#pragma once
#include "OccurrenceMineralTypeEnum.generated.h"

// Тип залегания полезных ископаеиых.
UENUM(BlueprintType)
enum OccurrenceMineralTypeEnum
{
	// На поверхности.
	OnSurface UMETA(DisplayName = "On Surface"),

	// Неглубоко под поверхностью.
	UnderNearSurface UMETA(DisplayName = "Under Near Surface"),

	// Неглубоко под поверхностью.
	UnderDeepSurface UMETA(DisplayName = "Under Deep Surface"),
};
