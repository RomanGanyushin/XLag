#pragma once
#include "XLagDynamicTerrainMapItemLayerStruct.h"

class XLagDynamicTerrainMapItemLayerStructCreator
{
public:
	static FXLagDynamicTerrainMapItemLayerStruct Create(const float& level, TerrainElementEnum element)
	{
		FXLagDynamicTerrainMapItemLayerStruct result;
		result.MineralId = 0;
		result.Element = element;
		result.Level = level;
	}
};