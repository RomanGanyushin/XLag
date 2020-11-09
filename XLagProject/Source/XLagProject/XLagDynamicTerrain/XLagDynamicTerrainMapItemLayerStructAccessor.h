#pragma once
#include "XLagDynamicTerrainMapItemLayerStruct.h"

class XLagDynamicTerrainMapItemLayerStructAccessor
{
public:
	XLagDynamicTerrainMapItemLayerStructAccessor(FXLagDynamicTerrainMapItemLayerStruct&  dynamicTerrainMapItemLayer) :
		_dynamicTerrainMapItemLayer(dynamicTerrainMapItemLayer)
	{
	}

	bool IsTerrainElement(const TerrainElementEnum element) const
	{
		return _dynamicTerrainMapItemLayer.Element == element;
	}

	float GetLevel() const
	{
		return _dynamicTerrainMapItemLayer.Level;
	}

	void ChangeLevel(const float& newLevel)
	{
		_dynamicTerrainMapItemLayer.Level = newLevel;
	}

	TerrainElementEnum GetTerrainElement() const
	{
		return _dynamicTerrainMapItemLayer.Element;
	}

	void ChangeTerrainElement(const TerrainElementEnum newElement)
	{
		_dynamicTerrainMapItemLayer.Element = newElement;
	}

	int GetMineralId() const
	{
		return _dynamicTerrainMapItemLayer.MineralId;
	}

	void SetMineralId(const int mineralId)
	{
		_dynamicTerrainMapItemLayer.MineralId = mineralId;
	}

private:
	FXLagDynamicTerrainMapItemLayerStruct&  _dynamicTerrainMapItemLayer;
};