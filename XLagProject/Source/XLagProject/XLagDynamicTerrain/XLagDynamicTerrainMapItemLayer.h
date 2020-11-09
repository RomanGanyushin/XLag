#pragma once
#include "../Common/TerrainElementEnum.h"
#include "XLagDynamicTerrainMapItemLayer.generated.h"

USTRUCT(BlueprintType)
struct FXLagDynamicTerrainMapItemLayer
{
	GENERATED_BODY()

	FXLagDynamicTerrainMapItemLayer() {};

	FXLagDynamicTerrainMapItemLayer(const float& level, const TerrainElementEnum& element)
		:Level(level), Element(element), MineralId(0)
	{
	}

	FXLagDynamicTerrainMapItemLayer(const float& level, const TerrainElementEnum& element, const int& mineralId)
		:Level(level), Element(element), MineralId(mineralId)
	{
	}

	UPROPERTY() float Level;
	UPROPERTY() TEnumAsByte <TerrainElementEnum> Element;
	UPROPERTY() int MineralId;
};