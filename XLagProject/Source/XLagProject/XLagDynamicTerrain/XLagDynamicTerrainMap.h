#pragma once
#include "XLagDynamicTerrainMapItem.h"
#include "XLagDynamicTerrainMap.generated.h"

USTRUCT(BlueprintType)
struct FXLagDynamicTerrainMap
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FXLagDynamicTerrainMapItem> Map;

	UPROPERTY() 
	int SizeX;

	UPROPERTY()
	int SizeY;

	UPROPERTY()
	float Scale;
};